# DragonSlayer

The game DragonSlayer has been developed for Project #1 in the class CPSC-2720 at the University of Lethbridge.

The development team consists of:

* Developer and Repo Manager: `John Holloway (holj2721)`
* Developer: `Dorgee Lama (lamd2721)`
* Developer: `John Nisperos (nisj2721)`

## Important Disclaimer

Due to the dependency requirement of the ncurses library (see below), the application will not build on the cs.uleth.ca
server. This dependency, while commonly preinstalled on most Linux distributions and Unix-like systems, is not installed
and cannot be found by the linker during the compilation process. As a result, the pipeline will always end at the build
phase

Please note: This only effects the gitlab server, the application will successfully build on the Ubuntu Linux virtual
machines required by the course.

## Dependencies

- `ncurses` (version 6.0 or higher): Required for terminal-based user interface
- C++ Compiler: Either
    - `gcc` >= 7.0 or higher
    - `clang` >= 5.0 or higher
    - or any C++ compiler that supports the C++ 17 standard.
- `gmake` if on FreeBSD. Needed because Makefile contains `ifeq` statements, which are not supported by base
  system's `make` utility.

run make on Linux, gmake on FreeBSD

## Installation

To build the game please run the following commands

```bash
git clone http://gitlab.cs.uleth.ca/holj2721/dragonslayer.git
```

To build the main game navigate to the downloaded directory and run the following command:

```bash
make compile
```

A binary executable will be produced. To start the game simply run the dragonSlayer executable

```bash
./dragonSlayer
```

## Tests and Documentation

### Quality Checks

The source code adheres the Google C++ coding style.  
To perform a style check on the source code, please run the following command:

```bash
make style
```

To perform a static analysis of the source code