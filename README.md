# ImoriaPlus

ImoriaPlus is a terminal roguelike that plays like **Imoria**, built on the
**Umoria** 5.7 engine. The display is still curses. The game rules and the
curses screen are separate, so a browser build can be added later.

Imoria (University of Washington, version 4.85) added races, classes, songs,
a larger town, and many creatures on top of Moria. Its VMS Pascal source is
the rules reference: [dungeons-of-moria/imoria](https://github.com/dungeons-of-moria/imoria).
Credits there: Kenneth Case, Mary Conner, Robert DeLoura, Dan Flye, Todd
Gardiner, Dave Jungck, Andy Walker, and Dean Yasuda.

Umoria is Robert Alan Koeneke's _Dungeons of Moria_, ported from VMS Pascal to
C by James E. Wilson and maintained as
[dungeons-of-moria/umoria](https://github.com/dungeons-of-moria/umoria).
This tree keeps that history, the GPL-3.0 license, and the Umoria attribution.
What is still to be brought across from Imoria is listed in [ROADMAP.md](ROADMAP.md).

_The Dungeons of Moria_ is a single player dungeon simulation originally
written by Robert Alan Koeneke, with its first public release in 1983.
The game was originally developed using VMS Pascal before being ported to the
C language by James E. Wilson in 1988, and released as _Umoria_.

Moria/Umoria has had many variants over the years, with [_Angband_](http://rephial.org/)
being the most well known. Umoria was also an inspiration for one the most
commercially successful action roguelike games, _Diablo_!

Supported Platforms:

  - Windows
  - macOS
  - Linux (Ubuntu/Debian)

Compiling and limited testing has been done for other Linux based system
including NetBSD 8.1 and Fedora 32.


## Umoria 5.7.x releases

The main focus of the `5.7.0` release was to provide support for the three
main operating systems: Windows, macOS, and Linux. Support for all other
outdated computer systems such as MS DOS, "Classic" Mac OS (pre OSX), Amiga,
and Atari ST was removed.

_Note: there have been no intentional gameplay changes in the 5.7.x releases._

Since the initial 5.7 release, a great deal of _code restoration_ has been
undertaken in the hope of aiding future development of the game. Some examples
of the work done include reformatting the source code with the help of
`clang-tidy` and `clang-format`, modernizing the code to use standard C types,
breaking apart most large functions (many of which had hundreds of lines of code)
into smaller, easier to read functions, and fixing all compiler warnings when
compiling against recent versions of GCC and Clang.

Full details of all changes can be found in the [CHANGELOG](CHANGELOG.md), and
by browsing the commit history.

Due to its lack of Windows and macOS support Moria was inaccessible to many
people. Hopefully these changes will give many more people a chance to play
this classic roguelike game.


## Notes on Compiling ImoriaPlus

The game builds with CMake, a C++14 compiler (clang or GCC), and ncurses.
It has been tested against GCC and ncurses 6.x. macOS needs the Xcode
command-line tools (clang) and ncurses, which ships with the system.


### macOS and Linux

From the repository root:

    $ cmake -S . -B build
    $ cmake --build build

The game and its data files are written to `build/imoriaplus/`. Run:

    $ ./build/imoriaplus/imoriaplus

A headless smoke test rolls every legal race and class, then generates the
town and the first dungeon level:

    $ ./build/imoriaplus/imoriaplus_smoke


### Windows

MinGW is used to provide GCC and GNU Binutils for compiling on the Windows platform.
The easiest solution to get set up is to use the [MSYS2 Installer](http://msys2.github.io/).
Once installed, `pacman` can be used to install `GCC`, `ncurses`, and the
`make`/`cmake` build tools.

At present an environment variable for the MinGW system being compiled on will
need to be specified. This will be either `mingw64` or `mingw32`.

At the command prompt type the following, being sure to add the correct label
to `MINGW=`:

    $ MINGW=mingw64 cmake .
    $ make

To perform an out-of-source build, type the following:

    $ mkdir build
    $ cd build
    $ MINGW=mingw64 cmake ..
    $ make

As with the macOS/Linux builds, all files will be installed into an `imoriaplus` directory.


## Historical Documents

Most of the original document files included in the Umoria 5.6 sources have
been placed in the [historical](historical) directory. You will even find the
old CHANGELOG, which tracks all code changes made between versions 4.81 and
5.5.2 (1987-2008). If you'd like to learn more on the development history of
Umoria, these can make for interesting reading.

There is also the original Moria Manual and FAQ. Although these are a little
outdated now they are certainly worth reading as they contain a lot of
interesting and useful information.


## Code of Conduct and Contributions

See here for details on our [Code of Conduct](CODE_OF_CONDUCT.md).

For details on how to contribute to the Umoria project, please read our
[contributing](CONTRIBUTING.md) guide.


## License Information

Umoria is released under the [GNU General Public License v3.0](LICENSE).

In 2007 Ben Asselstine and Ben Shadwick started the
[_free-moria_](http://free-moria.sourceforge.net/) project to re-license
UMoria 5.5.2 under GPL-2 by obtaining permission from all the contributing
authors. A year later they succeeded in their goal and in late 2008 official
maintainer David Grabiner released Umoria 5.6 under a GPL-3.0-or-later license.
