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
#include "../inc/DefaultInputFileReader.hpp"

// --- BOOST Includes ---
#include "boost/test/unit_test.hpp"

namespace adhocpp {
namespace utilities {

BOOST_AUTO_TEST_SUITE ( DefaultInputFileReader_test )

struct Fixture
{
  std::string fileName;
  PlaceHolderValueMap result;

  Fixture( )
  {
    fileName = "defaultInputFileReaderData.in";
  }
};

BOOST_FIXTURE_TEST_SUITE ( parseInputFile, Fixture )

BOOST_AUTO_TEST_CASE ( parseInputFile )
{
  BOOST_CHECK_NO_THROW( result = DefaultInputFileReader::parseInputFile( fileName ) );

  BOOST_CHECK_EQUAL( result.size( ), 6 );
  BOOST_CHECK_EQUAL( result["doubleArgument"], "1.23" );
  BOOST_CHECK_EQUAL( result["intArgument"], "23" );
  BOOST_CHECK_EQUAL( result["stringArgument"], "Hallo_Welt" );
  BOOST_CHECK_EQUAL( result["sizeArgument"], "34" );
  BOOST_CHECK_EQUAL( result["bool1"], "0" );
  BOOST_CHECK_EQUAL( result["bool2"], "true" );
}

BOOST_AUTO_TEST_SUITE_END() /* end of parseInputFile Test Suite */

BOOST_AUTO_TEST_SUITE_END() // DefaultInputFileReader_test 

}// namespace utilities 
}// namespace adhocpp
