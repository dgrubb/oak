# Oak

![Oak logo](./docs/oak_logo.png)

## What?

This project is an emulator for the [Acorn Archimedes](https://en.wikipedia.org/wiki/Acorn_Archimedes)
computer, famous for introducing the [ARM procesor](https://en.wikipedia.org/wiki/ARM_Architecture).

See the [Ultimate Acorn Archimedes talk](https://youtube.com/watch?v=Hf67JYkUCHQ) for more background on the machine.

## Why?

Simply to develop a comprehensive understanding of the ARM processor and the sheer
enjoyment of it. Consequently, although I'm aiming for a high level of compatibilty and
functionality of at least one popular Archimedes model (likely the A3000 for both
its popularity and the wealth of available technical documentation), that shall
be a secondary consideration. Don't expect all games and software to run seamlessly
(or at all, really, ahem).

If you're here searching for a decent emulation experince there are several
fabulous Archimedes emulators available:

[ArcEm](http://arcem.sourceforge.net)
[arculator](http://b-em.bbcmicro.com/arculator)
[RPCEmu](https://www.marutan.net/rpcemuspoon)

and you can even run [RISC OS on a Raspberry Pi!](https://www.riscosopen.org/content/downloads/raspberry-pi)

## Structure

* docs: Contains contemporary technical documentation about the Archimedes.
* source: Source for project.
* include: Header files for the project.
* test: GMock test cases.

## Usage

```
Usage:
$ ./Oak [arguments]
```

Arguments:

    -h   Show usage
    -l   Set log level (e.g., ./Oak -l DEBUG). Default INFO. Options:
            TRACE
            DEBUG
            INFO
            WARN
            ERROR
            CRITICAL
    -r  Specify ROM file (e.g., ./Oak -r myROM). Defaults to ./riscos-3.71.rom

**N.B.,** ROM files for RISC OS 3.71 are available legally at [4corn.co.uk.](https://www.4corn.co.uk/articles/rpcemu371win/)

```
$ curl -O https://www.4corn.co.uk/archive/roms/riscos3_71.zip && unzip riscos3_71.zip
```

or:

```
$ wget https://www.4corn.co.uk/archive/roms/riscos3_71.zip && unzip riscos3_71.zip
```

# Requirements

The usual tooling for compiling C++ with clang under Linux and the SDL development libraries. Under Debian/Ubuntu:

```
$ sudo apt-get install clang cmake build-essential libsdl2-2.0-0 libsdl2-dev
libsdl2-image-2.0-0 libsdl2-image-dev libconfig-dev google-mock googletest googletest-tools libgmock-dev
```

## Compilation

```
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
$ cmake --build .
```

## Execute Unit Tests

To run complete suite, execute the Oak-utmain binary without arguments:

```
$ cd build/test
$ ./Oak-utmain
```

To list available tests:

```
$ cd build/test
$ ./Oak-utmain --gtest_list_tests
```

To execute specific tests by filter:

```
$ cd build/test
$ ./Oak-utmain --gtest_list_tests=RegisterFile*
```
