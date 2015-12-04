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
#include "../inc/AutoArgsException.hpp"

// --- Catch Includes ---
#include "catch.hpp"

// --- Standard Includes ---
#include <string>
#include <iostream>
#include <sstream>

using namespace autoargs;

TEST_CASE ( "Default callling what" )
{
  std::stringstream out;
  std::streambuf *coutbuf = std::cout.rdbuf( ); //save old buf
  std::cout.rdbuf( out.rdbuf( ) ); //redirect std::cout to out.txt!

  {
    AutoArgsException error( "You did something wrong" );

    std::string errorMessage;

    CHECK_NOTHROW( errorMessage = error.what( ) );

    CHECK( errorMessage == "You did something wrong" );
  }

  CHECK( out.str( ) == "" );

  std::cout.rdbuf( coutbuf ); //reset to standard output again
}

TEST_CASE ( "Default not callling what" )
{
  std::stringstream out;
  std::streambuf *coutbuf = std::cout.rdbuf( ); //save old buf
  std::cout.rdbuf( out.rdbuf( ) ); //redirect std::cout to out.txt!

  {
    AutoArgsException error( "You did something wrong" );
  }

  CHECK( out.str( ) == "Error: You did something wrong\n" );

  std::cout.rdbuf( coutbuf ); //reset to standard output again
}
