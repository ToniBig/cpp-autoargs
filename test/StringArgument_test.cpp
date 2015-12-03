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

// --- BOOST Includes ---
#include "boost/test/unit_test.hpp"

namespace adhocpp
{
namespace utilities
{

BOOST_AUTO_TEST_SUITE ( StringArgumentTest )

BOOST_AUTO_TEST_SUITE ( Constructor )

BOOST_AUTO_TEST_CASE ( DefaultConstructorWithOutExplicitDefault )
{
  ArgumentManager::getInstance( ).clear( );
  BOOST_CHECK_NO_THROW( StringArgument( "stringOption", "Yes or no?" ) );
}

BOOST_AUTO_TEST_CASE ( DefaultConstructorWithExplicitDefault )
{
  ArgumentManager::getInstance( ).clear( );
  BOOST_CHECK_NO_THROW( StringArgument( "stringOption", "Yes or no?", "Hello World" ) );
}

BOOST_AUTO_TEST_SUITE_END() // Constructor

struct Fixture
{
  std::string result;

  ~Fixture( )
  {
    ArgumentManager::getInstance( ).clear( );
  }
};

BOOST_FIXTURE_TEST_SUITE( someFunction, Fixture )

BOOST_AUTO_TEST_CASE ( conversionUsingDefault )
{
  StringArgument argument( "stringOption", "Yes or no?" );

  BOOST_CHECK_THROW( result = argument, std::runtime_error );
}

BOOST_AUTO_TEST_CASE ( conversionUsingNonDefault )
{
  StringArgument argument( "stringOption", "Yes or no?", "No" );

  BOOST_CHECK_NO_THROW( result = argument );

  BOOST_CHECK_EQUAL( result, "No" );
}

BOOST_AUTO_TEST_SUITE_END() // someFunction

BOOST_AUTO_TEST_SUITE_END() // StringArgumentTest

}// namespace utilities
}// namespace adhocpp
