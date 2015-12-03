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
#include "../inc/StringArgument.hpp"
#include "../inc/ArgumentManager.hpp"

// --- Catch Includes ---
#include "catch.hpp"

namespace adhocpp
{
namespace utilities
{

TEST_CASE ( "String Argument: Default constructor with out explicit default" )
{
  ArgumentManager::getInstance( ).clear( );
  CHECK_NOTHROW( StringArgument( "stringOption", "Yes or no?" ) );
}

TEST_CASE ( "Default constructor with explicit default" )
{
  ArgumentManager::getInstance( ).clear( );
  CHECK_NOTHROW( StringArgument( "stringOption", "Yes or no?", "Hello World" ) );
}

struct Fixture
{
  std::string result;

  ~Fixture( )
  {
    ArgumentManager::getInstance( ).clear( );
  }
};

TEST_CASE_METHOD( Fixture, "String Argument" )
{

  SECTION( "conversionUsingDefault" ){
  StringArgument argument( "stringOption", "Yes or no?" );

  CHECK_THROWS_AS( result = argument, std::runtime_error );
}

SECTION( "conversionUsingNonDefault" )
{
  StringArgument argument( "stringOption", "Yes or no?", "No" );

  CHECK_NOTHROW( result = argument );

  CHECK( result == "No" );
}

}

} // namespace utilities
} // namespace adhocpp
