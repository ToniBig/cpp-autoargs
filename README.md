# cpp-autoargs

A simple command line argument parser for programs written in C++.


[![Build Status](https://travis-ci.org/ToniBig/cpp-autoargs.svg?branch=master)](https://travis-ci.org/ToniBig/cpp-autoargs) Master

[![Build Status](https://travis-ci.org/ToniBig/cpp-autoargs.svg?branch=development)](https://travis-ci.org/ToniBig/cpp-autoargs) Development


## Features

+ addition of new command line arguments using a single line 
+ automatic creating of documentation (help)
+ automatic creating of input files for every run
+ parsing of input files
+ support for customized arguments types, help messages and input file parsers

## Why?

During my PhD I was running a lot of non-linear simulations using C++. This meant writing a lot of driver files and playing around with input parameters all the time. I wrote `cpp-autoargs` to avoid having to recompile my drivers all the time for different parameters. This would of course all have been possible with other tools allready available, e.g. TCLAP or Boost Program Options. However, I wanted to simplify adding command line arguments and wanted to improve my C++ skills.

## Setting up

Currently you will have to compile the library and link it to your driver. The library can be build using CMake. I plan to add a (single) header only version in the future. That might not be the right answer for everyone (compile times <> template instantiations).

## Usage

Imagine you have some driver executable that prints useful information to the screen.
```c++
#include <iostream>

int main( int argc,
          char **argv )
{
  std::cout << "Hello World!" << std::endl;
  std::cout << "My name is John Doe." << std::endl;
  std::cout << "I am 33 years old." << std::endl;
  std::cout << "I am 1.92 m tall." << std::endl;
  std::cout << "I like telenovelas...not!" << std::endl;
}
```
which gives the following output
```
$ ./hello1
Hello World!
My name is John Doe.
I am 33 years old.
I am 1.92 m tall.
I like telenovelas.
```
To make this program more useful you would like to parametrize all of the data by assigning it to variables.
```c++
#include <iostream>
#include <string>

int main( int argc,
          char **argv )
{
  std::string first = "John";
  std::string last = "Doe";
  size_t age = 33;
  double height = 1.92;
  bool like = false;

  std::cout << "Hello World!" << std::endl;
  std::cout << "My name is " << first << " " << last << "." << std::endl;
  std::cout << "I am " << age << " years old." << std::endl;
  std::cout << "I am " << height << " m tall." << std::endl;
  std::cout << "I like telenovelas." << ( like ? "" : "..not!" ) << std::endl;
}
```
To control the behaviour of this program via the command line the variables can be turned into `cpp-autoargs`' arguments.
```c++
#include "../inc/autoargs.hpp"

using namespace autoargs;

int main( int argc,
          char **argv )
{
  StringArg first { "first", "The first name", "John" };
  StringArg last { "last", "The last name", "Doe" };
  SizeArg age { "age", "The (true?) age", 33 };
  DoubleArg height { "height", "How tall?", 1.92 };
  BoolArg like { "like", "You like not-jokes?", true };

  ArgumentParser::parseCommandLine( argc, argv );

  std::cout << "Hello World!" << std::endl;
  std::cout << "My name is " << *first << " " << last.value( ) << "." << std::endl;
  std::cout << "I am " << age << " years old." << std::endl;
  std::cout << "I am " << height << " m tall." << std::endl;
  std::cout << "I like telenovelas." << ( like ? "" : "..not!" ) << std::endl;
}
```
Additionally, we need to parse the command line after all the arguments have been initialized. Note, that the arguments can be directly used in place of the previous varibles. Should a conversion not take place automatically (the compiler will tell you), you can also convert the argument explicitly by calling the `value()` member function on the argument.
Now if the driver (`examples/hello3`) is called with the argument `--help` the automatically created documentation is printed.
```
$ ./hello3 --help
Usage: 
./hello3 [--options]
./hello3 --input inputFileName

Optional arguments:

	--age                     : size_t (33)                      : The (true?) age
	--first                   : string (John)                    : The first name
	--height                  : double (1.920000000000000e+00)   : How tall?
	--last                    : string (Doe)                     : The last name
	--like                    : bool (true)                      : You like not-jokes?

Built-In arguments:

	--help                    : print this help message
	--input                   : Process an input file

```


## Todos

* Add more documentation
