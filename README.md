# G7Reader
A small utility to read Rawthrills G7 Engine archive files. More info on this file format can be found on [my blog.](https://surasia.github.io/g7-reverse)

## Usage
`G7Reader.exe <input file> <output directory>`

## Building
This project includes Visual Studio 2022 project files but can be compiled via Clang/GCC/MSVC.
- Clang/GCC: `clang++/gcc -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic ./src/G7Reader.cpp -o G7Reader`