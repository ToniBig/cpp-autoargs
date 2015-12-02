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
#include "../inc/GenericNumericArgument.hpp"
#include "../inc/ArgumentManager.hpp"

// --- BOOST Includes ---
#include "boost/test/unit_test.hpp"

// --- Boost Includes ---
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

typedef boost::mpl::list<int,short,double,float,size_t> test_types;

namespace adhocpp
{
namespace utilities
{

BOOST_AUTO_TEST_SUITE ( GenericNumericArgumentTest )

BOOST_AUTO_TEST_SUITE ( Constructor )

BOOST_AUTO_TEST_CASE_TEMPLATE( DefaultConstructorWithOutExplicitDefault, T, test_types ){
ArgumentManager::getInstance( ).clear( );
BOOST_CHECK_NO_THROW( GenericNumericArgument<T>( "numericOption", "What?" ) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( DefaultConstructorWithExplicitDefault, T, test_types ){
ArgumentManager::getInstance( ).clear( );
BOOST_CHECK_NO_THROW( GenericNumericArgument<T>( "numericOption", "What?", 1 ) );
}

BOOST_AUTO_TEST_SUITE_END() // Constructor

struct Fixture
{
  ~Fixture( )
  {
    ArgumentManager::getInstance( ).clear( );
  }
};

#define UNUSED(expr) do { (void)(expr); } while (0)

BOOST_FIXTURE_TEST_SUITE( someFunction, Fixture )

BOOST_AUTO_TEST_CASE_TEMPLATE( conversionUsingDefault, T, test_types ){
GenericNumericArgument<T> argument( "numericOption", "Yes or no?" );

T result;

UNUSED( result );

BOOST_CHECK_THROW( result = argument, std::runtime_error );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( conversionUsingNonDefault, T, test_types ){
GenericNumericArgument<T> argument( "numericOption", "Yes or no?", 2 );

T result;

BOOST_CHECK_NO_THROW( result = argument );

BOOST_CHECK_EQUAL( result, 2 );
}

BOOST_AUTO_TEST_SUITE_END() // someFunction

BOOST_AUTO_TEST_SUITE_END() // GenericNumericArgumentTest

}// namespace utilities
}// namespace adhocpp
