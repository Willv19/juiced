# juiced

**juiced** is a suckless and lightweight battery daemon written in C. It notifies the user via libnotify about low battery. It is meant for minimal window managers.

It shows two warnings on two different battery levels.

Everything can be configured via a config.h file.

## Usage

### Installation

Be sure you satisfy the dependencies: libnotify.
Also you should have basic development tools like a C compiler and GNU make installed.
Then copy config.def.h to config.h and customize it to your needs.
(Re)Compile (and install) it (after modifications):

	$ make clean all
	# make install

### Starting

	$ juiced -d

## License

See [LICENSE](LICENSE).
