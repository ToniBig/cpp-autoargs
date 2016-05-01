// The MIT License (MIT)
//
// Copyright (c) 2013-2015 Tino Bog
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// --- Internal Includes ---
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
