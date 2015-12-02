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
