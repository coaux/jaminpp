# JAMin README

[JAMin][jamin] is a JACK Audio Mastering interface.

JAMin runs under the [JACK Audio Connection Kit][jack], a low-latency audio
server, which can connect a number of different applications to an
audio device, and also allow them to share audio among themselves.
JACK is different from other audio servers in being designed from the
ground up for professional audio work.  It focuses on two key areas:
synchronous execution of all clients, and low latency operation.

To get satisfactory results with JAMin, you will need to set your
system up to run JACK well.  See <http://jackit.sourceforge.net> for
details.


## COMPILING

You will need:

### Tools

- gcc >= 2.95
- autoconf >= 2.52
- automake >= 1.4
- libtool >= 1.4.2
- gettext >= 0.11.5
- [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/) >= 0.8.0

### Libraries

Recommended versions, where applicable, are shown under the general
requirement.

- [JACK][jack] >= 0.80.0
- [libxml2](https://gitlab.gnome.org/GNOME/libxml2) >= 2.5
- [GTK+](https://www.gtk.org) 3.0
- [Clutter](https://gitlab.gnome.org/Archive/clutter) >= 1.12.0
- Clutter-GTK >= 1.2.0
- [LADSPA SDK](https://www.ladspa.org)
- [swh-plugins](https://github.com/swh/ladspa) >= 0.4.6
- [fftw-3](https://www.fftw.org) >= 3.0.0
    - should have float support enabled
- [liblo](https://liblo.sourceforge.net/) >= 0.5
    - optional. If you have it installed, JAMin will support
	  scene changes over OSC and a commandline tool will be built

When compiling, you can request that JAMin links with the (default)
double precision FFTW library:
```bash
./configure --enable-double-fft
```
This is untested. You have been warned.

----

# jaminpp

[jaminpp][jaminpp] is an _unofficial fork_ of [jamin].

## Project Goals

### Immediate Goals

- Migrate the build system to [CMake](https://cmake.org/)
- Update the UI for GTK Builder (GNOME 3)
- Migrate `main` and the Jamin UI for gtkmm, glibmm, and related components in C++
- Add unit tests ([catch2](https://github.com/catchorg/Catch2/) version 3)

### Intermediate Goals

- Update packaging (Debian packaging) for distribution as jaminpp
- Provide packaging (spec file, testing) for latest Fedora releases

### Long-Term Goals (Tentative)

- Test for distribution on Microsoft Window platforms (Windows 7 to latest. clang, vcpkg, etc. ASIO?)
- Test for distribution both as a free/open source stand-alone application and 
  as a free/open source plugin using the [VST SDK](https://www.steinberg.net/developers/vstsdk/)


[jamin]: http://jamin.sourceforge.net
[jack]: https://jackaudio.org
[jaminpp]: https://github.com/coaux/jaminpp
