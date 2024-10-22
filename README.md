```

    ████████▄     ▄████████    ▄████████    ▄██████▄   ▄██████▄  ███▄▄▄▄
    ███   ▀███   ███    ███   ███    ███   ███    ███ ███    ███ ███▀▀▀██▄    
    ███    ███   ███    ███   ███    ███   ███    █▀  ███    ███ ███   ███    
    ███    ███  ▄███▄▄▄▄██▀   ███    ███  ▄███        ███    ███ ███   ███
    ███    ███ ▀▀███▀▀▀▀▀   ▀███████████ ▀▀███ ████▄  ███    ███ ███   ███ 
    ███    ███ ▀███████████   ███    ███   ███    ███ ███    ███ ███   ███
    ███   ▄███   ███    ███   ███    ███   ███    ███ ███    ███ ███   ███ 
    ████████▀    ███    ███   ███    █▀    ████████▀   ▀██████▀   ▀█   █▀
                 ███    ███                                                 

                 ▄████████  ▄█          ▄████████ ▄██   ▄      ▄████████    ▄████████ 
                ███    ███ ███         ███    ███ ███   ██▄   ███    ███   ███    ███ 
                ███    █▀  ███         ███    ███ ███▄▄▄███   ███    █▀    ███    ███ 
                ███        ███         ███    ███ ▀▀▀▀▀▀███  ▄███▄▄▄      ▄███▄▄▄▄██▀ 
              ▀███████████ ███       ▀███████████ ▄██   ███ ▀▀███▀▀▀     ▀▀███▀▀▀▀▀   
                       ███ ███         ███    ███ ███   ███   ███    █▄  ▀███████████ 
                 ▄█    ███ ███▌    ▄   ███    ███ ███   ███   ███    ███   ███    ███ 
               ▄████████▀  █████▄▄██   ███    █▀   ▀█████▀    ██████████   ███    ███ 
                           ▀                                               ███    ███ 
                   2024 J. Holloway, Dorgee Lama, and John Nisperos           

```

The game DragonSlayer has been developed for Project #1 in the class CPSC-2720 at the University of Lethbridge.

The development team consists of:

* Developer and Repo Manager: `John Holloway (holj2721)`
* Developer: `Dorgee Lama (lamd2721)`
* Developer: `John Nisperos (nisj2721)`

## Important Notice Regarding Gitlab Pipeline

Due to the dependency on the ncurses library (see below), the application will not build on the cs.uleth.ca
Gitlab server. While this library is commonly preinstalled on most Linux distributions and Unix-like systems, is not
installed on the Gitlab server and cannot be found by the linker during the compilation process. As a result, the
pipeline will always end at the build phase

*Please note:* This only effects the gitlab server, the application will successfully build on the Ubuntu Linux virtual
machines required by the course.

## Dependencies

- `ncurses` (version 6.0 or higher): Required for terminal-based user interface
- `googletest` (version 1.11 or higher): Required for building unit tests
- C++ Compiler: Either
    - `gcc` >= 7.0 or higher
    - `clang` >= 5.0 or higher
    - or any C++ compiler that supports the C++ 17 standard.
- `gmake` if on FreeBSD. Needed because Makefile contains `ifeq` statements, which are not supported by base
  system's `make` utility.

run make on Linux, gmake on FreeBSD

## Build

To build the game, run the following command:

```bash
git clone http://gitlab.cs.uleth.ca/holj2721/dragonslayer.git
```

After cloning the repository, navigate to the downloaded directory and run:

```bash
make compile
```

*Note:* On FreeBSD you will need to use `gmake` and not the base install `make` for all build, test and documentation
commands on this page

A binary executable will be produced. To start the game simply run the dragonSlayer executable

```bash
./dragonSlayer
```

## Tests and Documentation

### Quality Checks

#### Style Check

The source code adheres the Google C++ coding style.  
To perform a style check on the source code, please run the following command:

  ```bash
  make style
  ```

*Note:* The style check will require the application `cpplint` be installed

#### Static Check

To perform a static analysis of the source code please run the following command

  ```bash
  make static
  ```

*Note:* The static analysis will require that the application `cppcheck` be installed

### Unit Tests

To build and run unit tests please run the following command:

  ```bash
  make test
  ```

This will automatically build and run the googleTest unit tests for the application.

### Active Tests

To check the application for memory leaks, please run the following command:

  ```bash
  make memcheck
  ```

This command will run `valgrind` on the dragonSlayer_test binary produced for unit tests, checking for dynamically
allocated memory that has not been freed

*Note:* Due the interactive nature of the final game, it was not possible to automate memory checks on the final binary.
To manually check for memory leaks in the final game, first run `make compile` to build the main binary and run the
following command:

```bash
  valgrind ./dragonSlayer
```

### Documentation

#### Source Code Documentation

To build documentation for the C++ source code run the following command:

```bash
make docs
```

The file `./docs/code/html/index.html` will be built, providing information on the source code and objects in the game.

*Note:* To build documentation the application Doxygen is required to be installed

#### Coverage Tests and Reports

To build a coverage report for the unit tests, please run the following command

```bash
make coverage
```

A coverage test will be performed, and a report will be generated in the form of an HTML webpage. The application will
be built using `gcov` and `lcov` on Linux, and `llvm-cov` on FreeBSD. While the coverage results should be consistent
across both platforms, the styling of the report may differ depending on the tool used to create it. In both cases, the
report can be viewed by opening `./coverage/index.html`.

## Cleaning Build Directory

#### Clean Everything

To remove all object files and binary executables run the command

```bash
make clean
```

#### Clean Binaries

To remove the executables but leave the existing object files run the command

```bash
make clean-exec
```

#### Clean Objects

To remove only object files, please run the command

```bash
make clean-obj
```

#### Clean Source Code Documents

To remove the documentation on the source code, please run the command

```bash
make clean-docs
```

#### Clean Coverage test

To remove the documentation produced by the coveage test run the command

```bash
make clean-cov
```