# Sophia
> A simple functional programming language

[![Version: v0.0.0](https://img.shields.io/badge/version-v0.0.0-red)](https://vstan02.github.io/sophia)
[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](http://www.gnu.org/licenses/lgpl-3.0)

## Contents
- [Building and Installation](#building-and-installation)
  - [Dependencies](#dependencies)
  - [Building the project](#building-the-project)
  - [Running tests](#running-tests)
  - [Running the program](#running-the-program)
  - [Installing](#installing)
- [License](#license)
- [Contributing](#contributing)

## Building and Installation

### Dependencies
- C++ compiler (gcc, clang, ...)
- Build system generator: cmake

### Building the project
To set the compiler that will be used, you can use:
```sh
# for clang
export CC=/usr/bin/clang
export CC=/usr/bin/clang++

# for gcc
export CC=/usr/bin/gcc
export CC=/usr/bin/g++
```

To compile the project, we first need to make 'build.sh' script to be executable with:
```sh
chmod +x ./build.sh
```

Now, we can use 'build.sh' script to compile the project:
```sh
./build.sh
```

Or, you can do it without using 'build.sh'. 
To build the project, we first need to create a separate build directory and `cd` into it:
```sh
mkdir build
cd build
```

Now that we've created our build directory (assuming it's created in the project root), we can run `cmake` (we need to pass the parent directory path to them, which is where the `CMakeLists.txt` file is located):
```sh
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
```

Once `cmake` is done generating makefiles, we can build the app by running `make` inside our build directory:
```sh
make
```

### Running the program
If everything went well with the compilation we can run the executable:
```sh
./sophia
```

### Installing
To install the app run:
```sh
sudo make install
```
By default the app will be installed in `/usr/local/bin/` directory.

## License
Thalia is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
For more details, see [LICENSE](https://github.com/vstan02/sophia/blob/master/LICENSE) file.

## Contributing
Contributions are welcome.
If you have a feature request, or have found a bug, feel free to open a [new issue](https://github.com/vstan02/sophia/issues/new).
If you wish to contribute code, see [CONTRIBUTING.md](https://github.com/vstan02/sophia/blob/master/CONTRIBUTING.md) for more details.
