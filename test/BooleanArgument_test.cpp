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
#include "../inc/BooleanArgument.hpp"
#include "../inc/ArgumentManager.hpp"

// --- BOOST Includes ---
#include "boost/test/unit_test.hpp"

namespace adhocpp
{
namespace utilities
{

BOOST_AUTO_TEST_SUITE ( BooleanArgumentTest )

BOOST_AUTO_TEST_SUITE ( Constructor )

BOOST_AUTO_TEST_CASE ( DefaultConstructorWithOutExplicitDefault )
{
  ArgumentManager::getInstance( ).clear( );
  BOOST_CHECK_NO_THROW( BooleanArgument( "boolOption", "Yes or no?" ) );
}

BOOST_AUTO_TEST_CASE ( DefaultConstructorWithExplicitDefault )
{
  ArgumentManager::getInstance( ).clear( );
  BOOST_CHECK_NO_THROW( BooleanArgument( "boolOption", "Yes or no?", true ) );
}

BOOST_AUTO_TEST_SUITE_END() // Constructor

struct Fixture
{
  bool result;

  ~Fixture( )
  {
    ArgumentManager::getInstance( ).clear( );
  }
};

BOOST_FIXTURE_TEST_SUITE( someFunction, Fixture )

BOOST_AUTO_TEST_CASE ( conversionUsingDefault )
{
  BooleanArgument argument( "boolOption", "Yes or no?" );

  BOOST_CHECK_NO_THROW( result = argument );

  BOOST_CHECK_EQUAL( result, false );
}

BOOST_AUTO_TEST_CASE ( conversionUsingNonDefault )
{
  BooleanArgument argument( "boolOption", "Yes or no?", true );

  BOOST_CHECK_NO_THROW( result = argument );

  BOOST_CHECK_EQUAL( result, true );
}

BOOST_AUTO_TEST_SUITE_END() // someFunction

BOOST_AUTO_TEST_SUITE_END() // BooleanArgumentTest

}// namespace utilities
}// namespace adhocpp
