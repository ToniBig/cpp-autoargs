/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

// --- Internal Includes ---
#include "../inc/GenericArgumentParser.hpp"
#include "../inc/ArgumentManager.hpp"
#include "../inc/autoargs.hpp"

// --- BOOST Includes ---
#include "boost/test/unit_test.hpp"

namespace adhocpp {
namespace utilities {

using namespace autoargs;

BOOST_AUTO_TEST_SUITE ( GenericTestArgumentParserTest )

BOOST_AUTO_TEST_SUITE ( Constructor )

BOOST_AUTO_TEST_CASE ( Constructor )
{

}

BOOST_AUTO_TEST_SUITE_END() // Constructor

struct Fixture
{
  ~Fixture( )
  {
    ArgumentManager::getInstance( ).clear( );
  }
};

BOOST_FIXTURE_TEST_SUITE( parseCommandLine, Fixture )

BOOST_AUTO_TEST_CASE ( parseCommandLine )
{
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
  char* argv[] = { &arg0[0], &arg1[0], &arg2[0], &arg3[0], &arg4[0], NULL };

  BOOST_CHECK_NO_THROW( TestArgumentParser::parseCommandLine( argc, argv ) );

  double result1 = requiredArg1;
  double result2 = optionalArg1;
  double result3 = optionalArg2;
  bool result4 = optionalArg3;
  std::string result5 = optionalArg4;

  BOOST_CHECK_EQUAL( result1, 4.32 );
  BOOST_CHECK_EQUAL( result2, 6.54 );
  BOOST_CHECK_EQUAL( result3, 12 );
  BOOST_CHECK_EQUAL( result4, false );
  BOOST_CHECK_EQUAL( result5, "hello" );
}

BOOST_AUTO_TEST_CASE ( parseCommandLineWithInputFile )
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
  char* argv[] = { &arg0[0], &arg1[0], &arg2[0], NULL };

  BOOST_CHECK_NO_THROW( TestArgumentParser::parseCommandLine( argc, argv ) );

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

BOOST_AUTO_TEST_CASE ( optionalWithoutDashFails )
{
  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );

  int argc = 1 + 1;
  char arg0[] = "driver";
  char arg1[] = "optional1=6.54";
  char* argv[] = { &arg0[0], &arg1[0], NULL };

  {
    BOOST_CHECK_THROW( TestArgumentParser::parseCommandLine( argc, argv ), std::exception );
  }
}

BOOST_AUTO_TEST_CASE ( optionalWithoutAssignmentFails )
{
  DoubleArg optionalArg1( "optional1", "First optional", 1.23 );

  int argc = 1 + 1;
  char arg0[] = "driver";
  char arg1[] = "--optional1";
  char* argv[] = { &arg0[0], &arg1[0], NULL };

  BOOST_CHECK_THROW( TestArgumentParser::parseCommandLine( argc, argv ), std::exception );
}

BOOST_AUTO_TEST_CASE ( missingRequiredArgumentsFails )
{
  DoubleArg requiredArg1( "required", "First required" );

  int argc = 1;
  char arg0[] = "driver";
  char* argv[] = { &arg0[0], NULL };

  BOOST_CHECK_THROW( TestArgumentParser::parseCommandLine( argc, argv ), std::exception );
}

BOOST_AUTO_TEST_CASE ( optionalInsteadOfRequiredArgumentFails )
{
  DoubleArg requiredArg1( "required", "First required" );

  int argc = 2;
  char arg0[] = "driver";
  char arg1[] = "--optional1=10";
  char* argv[] = { &arg0[0], &arg1[0], NULL };

  BOOST_CHECK_THROW( TestArgumentParser::parseCommandLine( argc, argv ), std::exception );
}

BOOST_AUTO_TEST_CASE ( listArguments )
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
  char* argv[] = { &arg0[0], &arg1[0], &arg2[0], &arg3[0], &arg4[0], &arg5[0], NULL };

  BOOST_CHECK_NO_THROW( TestArgumentParser::parseCommandLine( argc, argv ) );

  std::string result;
  std::string reference;
  reference += "                     required1 : 4.320000000000000e+00          # (double) First required\n";
  reference += "                     required2 : tino                           # (string) Second required\n";
  reference += "                     optional1 : 6.540000000000000e+00          # (double) First optional\n";
  reference += "                     optional2 : 12                             # (size_t) Second optional\n";
  reference += "                     optional3 : hello                          # (string) Third optional\n";

  BOOST_CHECK_NO_THROW( result = TestArgumentParser::listArguments( ) );
  BOOST_CHECK_EQUAL( result, reference );
}

BOOST_AUTO_TEST_SUITE_END() // parseCommandLine

BOOST_AUTO_TEST_SUITE_END() // GenericTestArgumentParserTest

}// namespace utilities
}// namespace adhocpp
