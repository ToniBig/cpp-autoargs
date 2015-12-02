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
