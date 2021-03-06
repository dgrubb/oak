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
* src: Source for project.

## Usage

```
Usage:
$ ./oak -d 4 -r <ROM FILE>
	-h	Print usage.
	-r	Path to RISC OS ROM file.
	-c	Path to configuration file.
	-d	Set debug level:

		0 - Critical
		1 - Error
		2 - Always
		3 - Warning
		4 - Info
		5 - Verbose
		6 - Ultra verbose
		99- Never
```

![Oak launcher](./docs/oak-launcher.png)

## Configuration file

Oak can be pre-configured at by referencing a settings file. By default Oak shall search for 
oak.cfg (included in this repository) which applies a configuration similar to an A3000. Custom 
configuration files can be supplied by the command line where the following settings can be used:

```
rom_file = "riscs-3.71.rom"; // Path to a RISC OS ROM file, see https://www.4corn.co.uk/aview.php?sPath=/roms
ram_size = 2000000;          // Amount of RAM to simulate in bytes, 2MB by default (same as a stock A3000)
cpu_frequency = 8000000;     // CPU frequency in hertz, 8MHz by default (same as a stock A3000)
log_level = 4;               // See Usage, INFO by default. Overriden if user invokes the -d option at runtime

```

# Requirements

The usual tooling for compiling C under Linux and the SDL development libraries. Under Debian/Ubuntu: 

```
$ sudo apt-get install gcc automake build-essential libsdl2-2.0-0 libsdl2-dev 
libsdl2-image-2.0-0 libsdl2-image-dev libconfig-dev
```

## Compilation

```
$ cd src && make
```


