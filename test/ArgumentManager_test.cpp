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

// --- Boost Includes ---
#include <boost/test/unit_test.hpp>

// --- Standard Includes ---
#include <iostream>
#include <sstream>

namespace adhocpp {
namespace utilities {

using namespace autoargs;

BOOST_AUTO_TEST_SUITE (ArgumentManagerTest)

BOOST_AUTO_TEST_CASE ( getInstance )
{
  BOOST_CHECK_NO_THROW( ArgumentManager::getInstance( ) );
}

struct Fixture
{
  ~Fixture( )
  {
    ArgumentManager::getInstance( ).clear( );
  }
};

BOOST_FIXTURE_TEST_SUITE( TestsWithArgumentManagerReset, Fixture )

BOOST_AUTO_TEST_CASE ( registerArgument )
{
  DoubleArg optionalArg1( "value1", "A value", 1.23 );
  DoubleArg optionalArg2( "value2", "A value", 1.23 );
  DoubleArg requiredArg( "value", "A value" );

  BOOST_CHECK_EQUAL( ArgumentManager::getInstance( ).getNumberOfOptionalArguments( ), 2 );
  BOOST_CHECK_EQUAL( ArgumentManager::getInstance( ).getNumberOfRequiredArguments( ), 1 );
}

BOOST_AUTO_TEST_CASE ( registerArgumentsFails )
{
  DoubleArg optionalArg1( "value1", "A value", 1.23 );
  DoubleArg optionalArg2( "value2", "A value", 1.23 );
  DoubleArg requiredArg( "value", "A value" );

  BOOST_CHECK_THROW( ArgumentManager::getInstance( ).registerArgument( optionalArg1 ), std::runtime_error );
  BOOST_CHECK_THROW( ArgumentManager::getInstance( ).registerArgument( optionalArg2 ), std::runtime_error );
  BOOST_CHECK_THROW( ArgumentManager::getInstance( ).registerArgument( requiredArg ), std::runtime_error );
}

BOOST_AUTO_TEST_CASE ( getNumberOfArguments )
{
  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );
  DoubleArg requiredArg1( "required1", "First required" );
  SizeArg optionalArg2( "optional2", "Second optional", 23 );
  BoolArg requiredArg2( "required2", "Second required" ); // Defaults to false
  StringArg optionalArg3( "optional3", "Third optional", "3.45" );

  BOOST_CHECK_EQUAL( ArgumentManager::getInstance( ).getNumberOfOptionalArguments( ), 4 );
  BOOST_CHECK_EQUAL( ArgumentManager::getInstance( ).getNumberOfRequiredArguments( ), 1 );
}

BOOST_AUTO_TEST_CASE ( setArgumentsUsingPlaceholderValueMap )
{
  PlaceHolderValueMap input = { { "doubleArgument", "1.23" }, { "intArgument", "23" }, { "stringArgument", "Hallo_Welt" }, { "sizeArgument", "34" }, {
      "bool1", "0" }, { "bool2", "true" } };

  DoubleArg autoArg1( "doubleArgument", "" );
  IntArg autoArg2( "intArgument", "" );
  StringArg autoArg3( "stringArgument", "" );
  SizeArg autoArg4( "sizeArgument", "" );
  BoolArg autoArg5( "bool1", "" );
  BoolArg autoArg6( "bool2", "" );

  BOOST_CHECK_NO_THROW( ArgumentManager::getInstance( ).setArguments( input ) );

  double result1 = autoArg1;
  int result2 = autoArg2;
  std::string result3 = autoArg3;
  size_t result4 = autoArg4;
  bool result5 = autoArg5;
  bool result6 = autoArg6;

  BOOST_CHECK_EQUAL( result1, 1.23 );
  BOOST_CHECK_EQUAL( result2, 23 );
  BOOST_CHECK_EQUAL( result3, "Hallo_Welt" );
  BOOST_CHECK_EQUAL( result4, 34 );
  BOOST_CHECK_EQUAL( result5, false );
  BOOST_CHECK_EQUAL( result6, true );
}
//
BOOST_AUTO_TEST_SUITE_END() // TestsWithArgumentManagerReset
//
BOOST_AUTO_TEST_SUITE_END()

}// namespace adhocpp
}// namespace utilities
