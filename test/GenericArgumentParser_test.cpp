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
#include "../inc/GenericArgumentParser.hpp"
#include "../inc/ArgumentManager.hpp"
#include "../inc/autoargs.hpp"

// --- Catch Includes ---
#include "catch.hpp"

namespace adhocpp
{
namespace utilities
{

using namespace autoargs;

struct Fixture
{
  ~Fixture( )
  {
    ArgumentManager::getInstance( ).clear( );
  }
};

TEST_CASE_METHOD( Fixture, "Parse command line" )
{

  SECTION( "parseCommandLine" ){
  ArgumentManager::getInstance( ).clear( );

  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );
  DoubleArg requiredArg1( "required1", "First required" );
  SizeArg optionalArg2( "optional2", "Second optional", 23 );
  BoolArg optionalArg3( "optional3", "Third optional" );
  StringArg optionalArg4( "optional4", "Fourth optional", "3.45" );

  int argc = 4 + 1;
  char arg0[] = "driver";
  char arg1[] = "4.32";
  char arg2[] = "--optional1=6.54";
  char arg3[] = "--optional2=12";
  char arg4[] = "--optional4=hello";
  char* argv[] =
  { &arg0[0], &arg1[0], &arg2[0], &arg3[0], &arg4[0], NULL};

  CHECK_NOTHROW( TestArgumentParser::parseCommandLine( argc, argv ) );

  double result1 = requiredArg1;
  double result2 = optionalArg1;
  double result3 = optionalArg2;
  bool result4 = optionalArg3;
  std::string result5 = optionalArg4;

  CHECK( result1 == 4.32 );
  CHECK( result2 == 6.54 );
  CHECK( result3 == 12 );
  CHECK( result4 == false );
  CHECK( result5 == "hello" );
}

SECTION( "parseCommandLineWithInputFile" )
{
  ArgumentManager::getInstance( ).clear( );

  DoubleArg autoArg1( "doubleArgument", "" );
  IntArg autoArg2( "intArgument", "" );
  StringArg autoArg3( "stringArgument", "" );
  SizeArg autoArg4( "sizeArgument", "" );
  BoolArg autoArg5( "bool1", "" );
  BoolArg autoArg6( "bool2", "" );

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

SECTION( "missingRequiredArgumentsFails" )
{
  DoubleArg requiredArg1( "required", "First required" );

  int argc = 1;
  char arg0[] = "driver";
  char* argv[] =
  { &arg0[0], NULL};

  CHECK_THROWS_AS( TestArgumentParser::parseCommandLine( argc, argv ), std::exception );
}

SECTION( "optionalInsteadOfRequiredArgumentFails" )
{
  DoubleArg requiredArg1( "required", "First required" );

  int argc = 2;
  char arg0[] = "driver";
  char arg1[] = "--optional1=10";
  char* argv[] =
  { &arg0[0], &arg1[0], NULL};

  CHECK_THROWS_AS( TestArgumentParser::parseCommandLine( argc, argv ), std::exception );
}

SECTION( "listArguments" )
{

  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );
  DoubleArg requiredArg1( "required1", "First required" );
  SizeArg optionalArg2( "optional2", "Second optional", 23 );
  StringArg requiredArg2( "required2", "Second required" );
  StringArg optionalArg3( "optional3", "Third optional", "3.45" );

  int argc = 5 + 1;
  char arg0[] = "driver";
  char arg1[] = "4.32";
  char arg2[] = "tino";
  char arg3[] = "--optional1=6.54";
  char arg4[] = "--optional2=12";
  char arg5[] = "--optional3=hello";
  char* argv[] =
  { &arg0[0], &arg1[0], &arg2[0], &arg3[0], &arg4[0], &arg5[0], NULL};

  CHECK_NOTHROW( TestArgumentParser::parseCommandLine( argc, argv ) );

  std::string result;
  std::string reference;
  reference += "                     required1 : 4.320000000000000e+00          # (double) First required\n";
  reference += "                     required2 : tino                           # (string) Second required\n";
  reference += "                     optional1 : 6.540000000000000e+00          # (double) First optional\n";
  reference += "                     optional2 : 12                             # (size_t) Second optional\n";
  reference += "                     optional3 : hello                          # (string) Third optional\n";

  CHECK_NOTHROW( result = TestArgumentParser::listArguments( ) );
  CHECK( result == reference );
}

}

} // namespace utilities
} // namespace adhocpp
