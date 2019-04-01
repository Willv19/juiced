/* See LICENSE file for copyright and license details. */

#include <err.h>
#include <libnotify/notify.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#undef strlcat
#undef strlcpy

#include "arg.h"
#include "strlcat.h"
#include "strlcpy.h"
#include "concat.h"

#include "config.h"

char *argv0;
char concat[];
static unsigned short int done;
static unsigned short int dflag;

#define num_batteries (sizeof(batteries) / sizeof(char *))

int main(int argc, char *argv[]) {
    ARGBEGIN {
    case 'd':
        dflag = 1;
        break;
    case 'v':
        printf("juiced %s (C) 2016 juiced engineers\n", VERSION);
        return 0;
    default:
        fprintf(stderr, "usage: %s [-dhv]\n", argv0);
        return 1;
    } ARGEND

    if (dflag && daemon(1, 1) < 0) {
        err(1, "daemon");
    }

    int perc_last = 101; // 101 so that even 100 will trigger a notification
                         // if it is selected
    while (!done) {
        int percs[num_batteries];

        // The maximum percentage out of all the batteries.
        // This is so that this triggers only when the last battery is low.
        int perc = 0;

        for (size_t i = 0; i < num_batteries; i++) {
            char state[12];
            FILE *percfile;
            FILE *statefile;

            ccat(3, "/sys/class/power_supply/", batteries[i], "/status");
            statefile = fopen(concat, "r");
            if (statefile == NULL) {
                warn("Failed to open file %s", concat);
                return 1;
            }
            fscanf(statefile, "%12s", state);
            fclose(statefile);

            if (strcmp(state, "Discharging") == 0) {
                ccat(3, "/sys/class/power_supply/", batteries[i], "/capacity");
                percfile = fopen(concat, "r");
                if (percfile == NULL) {
                    warn("Failed to open file %s", concat);
                    return 1;
                }
                fscanf(percfile, "%i", &percs[i]);
                fclose(percfile);
                if (perc < percs[i]) {
                    perc = percs[i];
                }
            } else {
                // Set the percentage to 101% if the battery is charging to
                // avoid a notification
                perc = 101;
            }
        }
        
        if (perc <= danger && perc_last > danger) {
            system(dangercmd);
        } else if (perc <= critical && perc_last > critical && notify_init("juiced")) {
            NotifyNotification *notification = notify_notification_new(
                "Warning", "Battery is critically low.", NULL);
            notify_notification_set_urgency(notification,
                                            NOTIFY_URGENCY_CRITICAL);
            notify_notification_show(notification, NULL);
            g_object_unref(notification);
            notify_uninit();
        } else if (perc <= warning && perc_last > warning && notify_init("juiced")) {
            NotifyNotification *notification =
                notify_notification_new("Notice", "Battery is low.", NULL);
            notify_notification_set_urgency(notification,
                                            NOTIFY_URGENCY_CRITICAL);
            notify_notification_show(notification, NULL);
            g_object_unref(notification);
            notify_uninit();
        }

        perc_last = perc;

        sleep(repeat);
	}

	return 0;
}
