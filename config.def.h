/* See LICENSE file for copyright and license details. */

/* batteries to check; the maximum battery percentage will be used */
static const char *batteries[] = {
    "BAT0", // Internal battery
    "BAT1"  // External battery
};

/* how often to check */
static const unsigned int repeat = 60;

/* order should be danger < critical < warning; numbers in percent; check is <= */
static const signed int warning = 25;
static const signed int critical = 10;
static const signed int danger = 3;

/* what command to run if battery is under "danger" value */
static const char dangercmd[] = "notify-send -u critical 'Critical' 'Hibernated system due to low battery' && systemctl hibernate";
