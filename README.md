# Advent Of Code 2025

These are my solutions to the 2025 version of [Advent of Code](https://adventofcode.com/), written in C++

## Setup

As with last year, I'm using some third party libraries, in particular [Compile Time Regular Expressions](https://github.com/hanickadot/compile-time-regular-expressions),
and will be using the [Conan](https://conan.io/) package manager as I'm already famailiar with it and it allows me to use some Python utilities like [aocd](https://github.com/wimglenn/advent-of-code-data)

### Prerequisits

- [Python](https://www.python.org/)
- [Conan](https://conan.io/) - `pip install conan`
- [CMake](https://cmake.org/) - `pip install cmake`
- [aocd](https://github.com/wimglenn/advent-of-code-data) - `pip install advent-of-code-data`, `pip install browser-cookie3`

### Dependencies

Dependencies are gathered with Conan.  AdventOfCodeUtils needs to be created in your local conan cache before use.  All other dependencies are retrieved from Conan Center.

- [AdventOfCodeUtils](https://github.com/MBraedley/AdventOfCodeUtils)
- [CTRE](https://github.com/hanickadot/compile-time-regular-expressions)

### Build

Tested with Visual Studio 2022 Pro 17.14.21

Perform first time setup for aocd:  Log into Advent Of Code and run `aocd-token` to retrieve your personal authentication token.
(Note, this doesn't seem to work properly with Chrome, try Firefox or follow the manual instructions.)

Each day, perform a `conan install` to retrieve that day's input automatically.

```powershell
conan install .
```

Open the folder in Visual Studio and build solution.  **Do not regenerate the CMake cache** as this has broken my psuedo-solution in the past.
Letting Visual Studio do the normal CMake stuff is fine.

## Bugs and Issues

...will not be fixed.  Once a day has been solved the code will only receive, at best, cosmetic updates and maybe "easy" performance improvements.
