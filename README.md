# EAN13 Barcode Generator

Implementation of the EAN13 encoding, which creates an image with the barcode, corresponding to the given code.

## Prerequisites

### UNIX

To be able to run the build process and the compilation itself, you should have the following components installed :

* GNU Make
* CMake

### Windows

On Windows, you can use this project in MSVS, only if you have the CMake component installed.

## Compilation

### UNIX

To build the application on UNIX-like systems, run the following commands (assuming, you are in the project's directory):
```bash
mkdir build && cd build
cmake ..
make
```

### Windows

To build this project on Windows, you should have Microsoft Visual Studio with installed CMake component (it can be enabled in Visual Studio Installer). After the installation, the project will be automatically build upon opening.

## Usage

### Arguments

There is only one argument : the code to use for the barcode generation. It should have 12 numbers from 0 to 9 (the 13th number is the a checksum, the program will handle it's generation) .


### Running

An example of running this application can be seen below :

```bash
./ean13 590035200236
```

### Output files

The output file will have the name "output.svn". This file is a vector image file, which contains only a black barcode on a white background. Numerical representation of the code is omitted in this project.
