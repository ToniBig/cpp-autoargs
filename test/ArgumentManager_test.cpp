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
#include <autoargs.hpp>
#include <test/catch.hpp>
#include <iostream>
#include <sstream>

using namespace autoargs;

TEST_CASE( "Tests with argument manager reset" )
{
  ArgumentManager::clear( );

  SECTION( "registerArgument" ){
  DoubleArg optionalArg1( "value1", "A value", 1.23 );
  DoubleArg optionalArg2( "value2", "A value", 1.23 );

  CHECK( ArgumentManager::getNumberOfArguments( ) == 2 );
}

  SECTION( "registerArgumentsFails" ){
  DoubleArg optionalArg1( "value1", "A value", 1.23 );
  DoubleArg optionalArg2( "value2", "A value", 1.23 );

  CHECK_THROWS_AS( ArgumentManager::registerArgument( optionalArg1 ), AutoArgsException );
  CHECK_THROWS_AS( ArgumentManager::registerArgument( optionalArg2 ), AutoArgsException );
}

  SECTION( "getNumberOfArguments" ){
  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );
  SizeArg optionalArg2( "optional2", "Second optional", 23 );
  StringArg optionalArg3( "optional3", "Third optional", "3.45" );

  CHECK( ArgumentManager::getNumberOfArguments( ) == 3 );
}

  SECTION( "setArgumentsUsingPlaceholderValueMap" ){
  PlaceHolderValueMap input =
  {
    { "doubleArgument", "1.23"},
    { "intArgument", "23"},
    { "stringArgument", "Hallo_Welt"},
    { "sizeArgument", "34"},
    { "bool1", "0"},
    { "bool2", "true"}};

  DoubleArg autoArg1( "doubleArgument", "",0 );
  IntArg autoArg2( "intArgument", "",0 );
  StringArg autoArg3( "stringArgument", "","0" );
  SizeArg autoArg4( "sizeArgument", "",0 );
  BoolArg autoArg5( "bool1", "",0 );
  BoolArg autoArg6( "bool2", "",0 );

  CHECK_NOTHROW( ArgumentManager::setArguments( input ) );

  double result1 = autoArg1;
  int result2 = autoArg2;
  std::string result3 = autoArg3;
  size_t result4 = autoArg4;
  bool result5 = autoArg5;
  bool result6 = autoArg6;

  CHECK( result1 == 1.23 );
  CHECK( result2 == 23 );
  CHECK( result3 == "Hallo_Welt" );
  CHECK( result4 == 34 );
  CHECK( result5 == false );
  CHECK( result6 == true );
}
}
