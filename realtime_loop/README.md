# Real-Time Gas Control System

![C](https://img.shields.io/badge/C-99-blue)
![License](https://img.shields.io/github/license/franneck94/CProjectTemplate)
![Linux Build](https://github.com/franneck94/CProjectTemplate/workflows/Ubuntu%20CI%20Test/badge.svg)

This project implements a real-time gas control system using modular C programming. The system includes components for gas sensing, actuation, display, and control logic, designed to operate in a real-time loop.

## Features

- Modular design with separate components for sensors, actuators, and display.
- Real-time control loop for gas system management.
- Unit testing using [Unity](https://github.com/ThrowTheSwitch/Unity).
- Code documentation with [Doxygen](http://www.stack.nl/~dimitri/doxygen/).
- Tooling: Clang-Format, Cmake-Format, Clang-tidy, Sanitizers.

## Structure

``` text
├── CMakeLists.txt
├── app
│   ├── CMakeLists.txt
│   └── main.c
├── cmake
│   └── cmake modules
├── docs
│   ├── Doxyfile
│   └── html/
├── external
│   ├── CMakeLists.txt
│   ├── ...
├── src
│   ├── CMakeLists.txt
│   ├── GasActuatorThread/
│   ├── GasControlEpochtime/
│   ├── GasControlExecutive/
│   ├── GasDisplayThread/
│   ├── GasSensorThread/
│   ├── Loop/
│   └── ShareData/
└── tests
    ├── CMakeLists.txt
    └── test_testbuilder.c
```

Library code goes into [src/](src/), main program code in [app/](app), and tests go in [tests/](tests/).

## Software Requirements

- CMake 3.21+
- GNU Makefile
- Doxygen
- GCC 9+ or Clang 9+
- Optional: Code Coverage (only on GNU|Clang): gcovr

## Building

First, clone this repo and do the preliminary work:

```shell
git clone --recursive https://github.com/franneck94/CProjectTemplate
make prepare
```

- App Executable

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --target main
cd app
./main
```

- Unit testing

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --target unit_tests
cd tests
./unit_tests
```

- Documentation

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug --target docs
```

- Code Coverage (Unix only)

```shell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON ..
cmake --build . --config Debug --target coverage
```

For more info about CMake see [here](./README_cmake.md).
