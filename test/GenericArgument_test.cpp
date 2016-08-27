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

using namespace autoargs;

TEST_CASE( "GenericArgument: Default constructor with explicit default, int" )
{
  ArgumentManager::clear( );
  CHECK_NOTHROW( GenericArgument<int>( "numericOption", "What?", 1 ) );
}

TEST_CASE( "GenericArgument: Default constructor with explicit default, short" )
{
  ArgumentManager::clear( );
  CHECK_NOTHROW( GenericArgument<short>( "numericOption", "What?", 1 ) );
}

TEST_CASE( "GenericArgument: Default constructor with explicit default, double" )
{
  ArgumentManager::clear( );
  CHECK_NOTHROW( GenericArgument<double>( "numericOption", "What?", 1 ) );
}

TEST_CASE( "GenericArgument: Default constructor with explicit default, float" )
{
  ArgumentManager::clear( );
  CHECK_NOTHROW( GenericArgument<float>( "numericOption", "What?", 1 ) );
}

TEST_CASE( "GenericArgument: Default constructor with explicit default, size_t" )
{
  ArgumentManager::clear( );
  CHECK_NOTHROW( GenericArgument<size_t>( "numericOption", "What?", 1 ) );
}

#define UNUSED(expr) do { (void)(expr); } while (0)

TEST_CASE( "Generic Argument" )
{
  ArgumentManager::clear( );

  SECTION( "conversion using non default int" ){
  GenericArgument<int> argument( "numericOption", "Yes or no?", 2 );

  int result;
  CHECK_NOTHROW( result = argument );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = argument.value() );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = *argument );
  CHECK( result == 2 );
}

  SECTION( "conversion using non default float" ){
  GenericArgument<float> argument( "numericOption", "Yes or no?", 2 );

  float result;
  CHECK_NOTHROW( result = argument );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = argument.value() );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = *argument );
  CHECK( result == 2 );
}

  SECTION( "conversion using non default double" ){
  GenericArgument<double> argument( "numericOption", "Yes or no?", 2 );

  double result;
  CHECK_NOTHROW( result = argument );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = argument.value() );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = *argument );
  CHECK( result == 2 );
}

  SECTION( "conversion using non default size_t" ){
  GenericArgument<size_t> argument( "numericOption", "Yes or no?", 2 );

  size_t result;
  CHECK_NOTHROW( result = argument );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = argument.value() );
  CHECK( result == 2 );

  CHECK_NOTHROW( result = *argument );
  CHECK( result == 2 );
}

}

TEST_CASE( "Generic Argument as String" )
{
  ArgumentManager::clear( );
  GenericArgument<std::string> argument( "stringOption", "Yes or no?", "No" );
  std::string result;

  SECTION( "Conversion" ){

  CHECK_NOTHROW( result = argument );
  CHECK( result == "No" );

  CHECK_NOTHROW( result = argument.value() );
  CHECK( result == "No" );

  CHECK_NOTHROW( result = *argument );
  CHECK( result == "No" );
}

}

TEST_CASE( "Generic Argument as Boolean" )
{
  ArgumentManager::clear( );

  GenericArgument<bool> argument( "boolOption", "Yes or no?", true );

  bool result;

  SECTION( "Implicit conversion" ){

  CHECK_NOTHROW( result = argument );

  CHECK( result == true );
}

  SECTION("conversion using value member"){

  CHECK_NOTHROW( result = argument.value() );

  CHECK( result == true );
}

  SECTION("conversion using dereferenciation"){

  CHECK_NOTHROW( result = *argument );

  CHECK( result == true );
}

}

