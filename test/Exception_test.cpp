/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/Exception.hpp"

// --- Boost Includes ---
#include <boost/test/unit_test.hpp>

// --- Standard Includes ---
#include <string>
#include <iostream>

namespace autoargs
{

BOOST_AUTO_TEST_SUITE ( ExceptionTest )

BOOST_AUTO_TEST_SUITE ( Constructor )

BOOST_AUTO_TEST_CASE ( Default )
{
  Exception error( "You did something wrong" );

  std::string errorMessage;

  BOOST_CHECK_NO_THROW( errorMessage = error.what() )
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

} // namespace autoargs
