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
#include "autoargs.hpp"

// --- Catch Includes ---
#include "catch.hpp"

using namespace autoargs;


TEST_CASE( "parse input file" )
{
  PlaceHolderValueMap result;
  std::string fileName = "defaultInputFileReaderData.in";

  SECTION( "parse input file" ){

  REQUIRE_NOTHROW( result = DefaultInputFileReader::parseInputFile( fileName ) );

  CHECK( result.size( ) == 6 );
  CHECK( result["doubleArgument"] == "1.23" );
  CHECK( result["intArgument"] == "23" );
  CHECK( result["stringArgument"] == "Hallo_Welt" );
  CHECK( result["sizeArgument"] == "34" );
  CHECK( result["bool1"] == "0" );
  CHECK( detail::to_lower(result["bool2"]) == "true" );
}

}
