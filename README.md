# cpp-autoargs

A simple command line argument parser for programs written in C++.


[![Build Status](https://travis-ci.org/ToniBig/cpp-autoargs.svg?branch=master)](https://travis-ci.org/ToniBig/cpp-autoargs)Master

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

## Todo

* Add documentation
