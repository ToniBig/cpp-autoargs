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
