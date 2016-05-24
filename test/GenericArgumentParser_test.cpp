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

struct Fixture
{
  ~Fixture( )
  {
    ArgumentManager::clear( );
  }
};

TEST_CASE_METHOD( Fixture, "Parse command line" )
{

  SECTION( "parseCommandLine" ){
  ArgumentManager::clear( );

  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );
  SizeArg optionalArg2( "optional2", "Second optional", 23 );
  StringArg optionalArg3( "optional3", "Fourth optional", "3.45" );

  int argc = 3 + 1;
  char arg0[] = "driver";
  char arg1[] = "--optional1=6.54";
  char arg2[] = "--optional2=12";
  char arg3[] = "--optional3=hello";
  char* argv[] =
  { &arg0[0], &arg1[0], &arg2[0], &arg3[0], NULL};

  CHECK_NOTHROW( TestArgumentParser::parseCommandLine( argc, argv ) );

  double result1 = optionalArg1;
  size_t result2 = optionalArg2;
  std::string result3 = optionalArg3;

  CHECK( result1 == 6.54 );
  CHECK( result2 == 12 );
  CHECK( result3 == "hello" );
}

SECTION( "parseCommandLineWithInputFile" )
{
  ArgumentManager::clear( );

  DoubleArg autoArg1( "doubleArgument", "", 0 );
  IntArg autoArg2( "intArgument", "", 0 );
  StringArg autoArg3( "stringArgument", "", "0" );
  SizeArg autoArg4( "sizeArgument", "", 0 );
  BoolArg autoArg5( "bool1", "", 0 );
  BoolArg autoArg6( "bool2", "", 0 );

  int argc = 1 + 2;
  char arg0[] = "driver";
  char arg1[] = "--input";
  char arg2[] = "defaultInputFileReaderData.in";
  char* argv[] =
  { &arg0[0], &arg1[0], &arg2[0], NULL};

  CHECK_NOTHROW( TestArgumentParser::parseCommandLine( argc, argv ) );

  double result1 = autoArg1;
  int result2 = autoArg2;
  std::string result3 = autoArg3;
  size_t result4 = autoArg4;
  bool result5 = autoArg5;
  bool result6 = autoArg6;

  CHECK( result1 == 1.23 );
  CHECK( result2 == 23 );
  CHECK( result3 == "Hallo_Welt" );
  CHECK( result4 == 34 );
  CHECK( result5 == false );
  CHECK( result6 == true );
}

SECTION( "optionalWithoutDashFails" )
{
  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );

  int argc = 1 + 1;
  char arg0[] = "driver";
  char arg1[] = "optional1=6.54";
  char* argv[] =
  { &arg0[0], &arg1[0], NULL};

  {
    CHECK_THROWS_AS( TestArgumentParser::parseCommandLine( argc, argv ), std::exception );
  }
}

SECTION( "optionalWithoutAssignmentFails" )
{
  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );

  int argc = 1 + 1;
  char arg0[] = "driver";
  char arg1[] = "--optional1";
  char* argv[] =
  { &arg0[0], &arg1[0], NULL};

  CHECK_THROWS_AS( TestArgumentParser::parseCommandLine( argc, argv ), std::exception );
}

SECTION( "listArguments" )
{

  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );
  SizeArg optionalArg2( "optional2", "Second optional", 23 );
  StringArg optionalArg3( "optional3", "Third optional", "3.45" );

  int argc = 3 + 1;
  char arg0[] = "driver";
  char arg1[] = "--optional1=6.54";
  char arg2[] = "--optional2=12";
  char arg3[] = "--optional3=hello";
  char* argv[] =
  { &arg0[0], &arg1[0], &arg2[0], &arg3[0], NULL};

  CHECK_NOTHROW( TestArgumentParser::parseCommandLine( argc, argv ) );

  std::string result;
  std::string reference;
  reference += "                     optional1 : 6.540000000000000e+00          # (double) First optional\n";
  reference += "                     optional2 : 12                             # (unsigned long) Second optional\n";
  reference += "                     optional3 : hello                          # (string) Third optional\n";

  CHECK_NOTHROW( result = TestArgumentParser::listArguments( ) );
  CHECK( result == reference );
}

}
