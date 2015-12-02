/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

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
