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
#include "../inc/AutoArgsException.hpp"

// --- Standard Includes ---
#include <iostream>

namespace adhocpp
{
namespace utilities
{

AutoArgsException::AutoArgsException( const std::string& message ) :
        message( message ),
        whatNotCalled( new bool( true ) )
{
}

AutoArgsException::~AutoArgsException( ) throw ( )
{
  try
  {
    if ( *whatNotCalled )
    {
      std::cout << "Error: " << message << std::endl;
    }
  }
  catch ( ... )
  {
  }
}

const char* AutoArgsException::what( ) const throw ( )
{
  *whatNotCalled = false;

  return message.c_str( );
}

} // namespace utilities
} // namespace adhocpp
