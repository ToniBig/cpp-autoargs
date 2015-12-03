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
#include "../inc/DefaultHelpMessageCreator.hpp"

// --- BOOST Includes ---
#include "boost/test/unit_test.hpp"

namespace adhocpp
{
namespace utilities
{

BOOST_AUTO_TEST_SUITE ( DefaultHelpMessageCreatorTest )

BOOST_AUTO_TEST_CASE ( getHelpDescription )
{

  DriverData data;

  data.driverName = "myFancyApp";

  data.description = "Compute something";

  data.requiredArguments.push_back( makeArgument( "required1", "First required", "double" ) );
  data.requiredArguments.push_back( makeArgument( "requiredTwo", "Second required", "double" ) );

  data.optionalArguments.push_back( makeArgument( "optional1", "First optional", "double", "1.23" ) );
  data.optionalArguments.push_back( makeArgument( "optional2", "Second optional", "size_t", "23" ) );
  data.optionalArguments.push_back( makeArgument( "optional3", "Third optional", "bool", "false" ) );
  data.optionalArguments.push_back( makeArgument( "optional4", "Fourth optional", "string", "3.45" ) );

  data.builtInArguments.push_back( makeArgument( "help", "print this help message" ) );
  data.builtInArguments.push_back( makeArgument( "version", "print the version of AdhoC++ being used" ) );

  std::string description;
  std::string reference =
      "Usage: \n"
      "myFancyApp required1 requiredTwo [--options]\n"
      "myFancyApp --input inputFileName\n"
      "\n"
      "Purpose: \n"
      "\n"
      "Compute something\n"
      "\n"
      "Required arguments:\n"
      "\n"
      "\trequired1                 : double                           : First required\n"
      "\trequiredTwo               : double                           : Second required\n"
      "\n"
      "Optional arguments:\n"
      "\n"
      "\t--optional1               : double (1.23)                    : First optional\n"
      "\t--optional2               : size_t (23)                      : Second optional\n"
      "\t--optional3               : bool (false)                     : Third optional\n"
      "\t--optional4               : string (3.45)                    : Fourth optional\n"
      "\n"
      "Built-In arguments:\n"
      "\n"
      "\t--help                    : print this help message\n"
      "\t--version                 : print the version of AdhoC++ being used\n";

  BOOST_CHECK_NO_THROW( description = DefaultHelpMessageCreator::getHelpMessage( data ) );

  BOOST_CHECK_EQUAL( description, reference );
}

BOOST_AUTO_TEST_SUITE_END() // DefaultHelpMessageCreatorTest

}// namespace utilities
}// namespace adhocpp
