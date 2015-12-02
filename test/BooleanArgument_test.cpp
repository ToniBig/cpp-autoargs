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
