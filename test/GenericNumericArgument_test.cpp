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
#include "../inc/GenericNumericArgument.hpp"
#include "../inc/ArgumentManager.hpp"

// --- Catch Includes ---
#include "catch.hpp"

using namespace autoargs;

TEST_CASE( "GenericNumericArgument: Default constructor with explicit default, int" )
{
  ArgumentManager::getInstance( ).clear( );
  CHECK_NOTHROW( GenericNumericArgument<int>( "numericOption", "What?", 1 ) );
}

TEST_CASE( "GenericNumericArgument: Default constructor with explicit default, short" )
{
  ArgumentManager::getInstance( ).clear( );
  CHECK_NOTHROW( GenericNumericArgument<short>( "numericOption", "What?", 1 ) );
}

TEST_CASE( "GenericNumericArgument: Default constructor with explicit default, double" )
{
  ArgumentManager::getInstance( ).clear( );
  CHECK_NOTHROW( GenericNumericArgument<double>( "numericOption", "What?", 1 ) );
}

TEST_CASE( "GenericNumericArgument: Default constructor with explicit default, float" )
{
  ArgumentManager::getInstance( ).clear( );
  CHECK_NOTHROW( GenericNumericArgument<float>( "numericOption", "What?", 1 ) );
}

TEST_CASE( "GenericNumericArgument: Default constructor with explicit default, size_t" )
{
  ArgumentManager::getInstance( ).clear( );
  CHECK_NOTHROW( GenericNumericArgument<size_t>( "numericOption", "What?", 1 ) );
}

#define UNUSED(expr) do { (void)(expr); } while (0)

TEST_CASE( "Generic Argument" )
{
  ArgumentManager::getInstance( ).clear( );

  SECTION( "conversion using non default int" ){
  GenericNumericArgument<int> argument( "numericOption", "Yes or no?", 2 );

  int result;
  CHECK_NOTHROW( result = argument );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = argument.value() );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = *argument );
  CHECK( result == 2 );
}

  SECTION( "conversion using non default float" ){
  GenericNumericArgument<float> argument( "numericOption", "Yes or no?", 2 );

  float result;
  CHECK_NOTHROW( result = argument );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = argument.value() );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = *argument );
  CHECK( result == 2 );
}

  SECTION( "conversion using non default double" ){
  GenericNumericArgument<double> argument( "numericOption", "Yes or no?", 2 );

  double result;
  CHECK_NOTHROW( result = argument );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = argument.value() );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = *argument );
  CHECK( result == 2 );
}

  SECTION( "conversion using non default size_t" ){
  GenericNumericArgument<size_t> argument( "numericOption", "Yes or no?", 2 );

  size_t result;
  CHECK_NOTHROW( result = argument );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = argument.value() );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = *argument );
  CHECK( result == 2 );
}

}
