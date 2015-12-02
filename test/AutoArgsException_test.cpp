/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */


//// --- Internal Includes ---
//#include "../inc/AutoArgsException.hpp"
//
//// --- UnitTest Includes ---
//#include "utilities/inc/unittest.hpp"
//
//namespace adhocpp
//{
//namespace utilities
//{
//
//// --- Standard Includes ---
//#include <string>
//#include <iostream>
//#include <sstream>
//
//BOOST_AUTO_TEST_SUITE ( AutoArgsExceptionTest )
//
//BOOST_AUTO_TEST_SUITE ( Constructor )
//
//BOOST_AUTO_TEST_CASE ( DefaultCalllingWhat )
//{
//  std::stringstream out;
//  std::streambuf *coutbuf = std::cout.rdbuf( ); //save old buf
//  std::cout.rdbuf( out.rdbuf( ) ); //redirect std::cout to out.txt!
//
//  {
//    AutoArgsException error( "You did something wrong" );
//
//    std::string errorMessage;
//
//    BOOST_CHECK_NO_THROW( errorMessage = error.what( ) )
//
//    BOOST_CHECK_EQUAL( errorMessage, "You did something wrong" );
//  }
//
//  BOOST_CHECK_EQUAL( out.str( ), "" );
//
//  std::cout.rdbuf( coutbuf ); //reset to standard output again
//}
//
//BOOST_AUTO_TEST_CASE ( DefaultNotCalllingWhat )
//{
//  std::stringstream out;
//  std::streambuf *coutbuf = std::cout.rdbuf( ); //save old buf
//  std::cout.rdbuf( out.rdbuf( ) ); //redirect std::cout to out.txt!
//
//  {
//    AutoArgsException error( "You did something wrong" );
//  }
////  std::string errorMessage;
//
//  BOOST_CHECK_EQUAL( out.str( ), "" );
//
//  std::cout.rdbuf( coutbuf ); //reset to standard output again
//}
//
//BOOST_AUTO_TEST_SUITE_END()
//
//BOOST_AUTO_TEST_SUITE_END()
//
//}// namespace utilities
//}// namespace adhocpp
