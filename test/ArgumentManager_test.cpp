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
#include "../inc/ArgumentManager.hpp"
#include "../inc/autoargs.hpp"

// --- Catch Includes ---
#include "catch.hpp"

// --- Standard Includes ---
#include <iostream>
#include <sstream>

namespace adhocpp
{
namespace utilities
{

using namespace autoargs;

TEST_CASE ( "getInstance" )
{
  CHECK_NOTHROW( ArgumentManager::getInstance( ) );
}

struct Fixture
{
  ~Fixture( )
  {
    ArgumentManager::getInstance( ).clear( );
  }
};

TEST_CASE_METHOD( Fixture, "Tests with argument manager reset" )
{
  SECTION( "registerArgument" ){
  DoubleArg optionalArg1( "value1", "A value", 1.23 );
  DoubleArg optionalArg2( "value2", "A value", 1.23 );
  DoubleArg requiredArg( "value", "A value" );

  CHECK( ArgumentManager::getInstance( ).getNumberOfOptionalArguments( ) == 2 );CHECK( ArgumentManager::getInstance( ).getNumberOfRequiredArguments( ) == 1 );
}

SECTION( "registerArgumentsFails" )
{
  DoubleArg optionalArg1( "value1", "A value", 1.23 );
  DoubleArg optionalArg2( "value2", "A value", 1.23 );
  DoubleArg requiredArg( "value", "A value" );

  CHECK_THROWS_AS( ArgumentManager::getInstance( ).registerArgument( optionalArg1 ), std::runtime_error );CHECK_THROWS_AS( ArgumentManager::getInstance( ).registerArgument( optionalArg2 ), std::runtime_error );CHECK_THROWS_AS( ArgumentManager::getInstance( ).registerArgument( requiredArg ),
      std::runtime_error );
}

SECTION( "getNumberOfArguments" )
{
  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );
  DoubleArg requiredArg1( "required1", "First required" );
  SizeArg optionalArg2( "optional2", "Second optional", 23 );
  BoolArg requiredArg2( "required2", "Second required" ); // Defaults to false
  StringArg optionalArg3( "optional3", "Third optional", "3.45" );

  CHECK( ArgumentManager::getInstance( ).getNumberOfOptionalArguments( ) == 4 );CHECK( ArgumentManager::getInstance( ).getNumberOfRequiredArguments( ) == 1 );
}

SECTION( "setArgumentsUsingPlaceholderValueMap" )
{
  PlaceHolderValueMap input =
  {
    { "doubleArgument", "1.23"},
    { "intArgument", "23"},
    { "stringArgument", "Hallo_Welt"},
    { "sizeArgument", "34"},
    {
      "bool1", "0"},
    { "bool2", "true"}};

  DoubleArg autoArg1( "doubleArgument", "" );
  IntArg autoArg2( "intArgument", "" );
  StringArg autoArg3( "stringArgument", "" );
  SizeArg autoArg4( "sizeArgument", "" );
  BoolArg autoArg5( "bool1", "" );
  BoolArg autoArg6( "bool2", "" );

  CHECK_NOTHROW( ArgumentManager::getInstance( ).setArguments( input ) );

  double result1 = autoArg1;
  int result2 = autoArg2;
  std::string result3 = autoArg3;
  size_t result4 = autoArg4;
  bool result5 = autoArg5;
  bool result6 = autoArg6;

  CHECK( result1 == 1.23 );CHECK( result2 == 23 );CHECK( result3 == "Hallo_Welt" );CHECK( result4 == 34 );CHECK( result5 == false );CHECK( result6 == true );
}
}

} // namespace adhocpp
} // namespace utilities
