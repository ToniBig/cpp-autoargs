/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/Exception.hpp"

// --- Standard Includes ---
#include <iostream>

namespace autoargs
{

inline Exception::Exception( const std::string& message ) :
    message( message ), whatNotCalled( new bool( true ) )
{
}

inline Exception::~Exception( ) throw ( )
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

const char* Exception::what( ) const throw ( )
{
  *whatNotCalled = false;

  return message.c_str( );
}

} // namespace autoargs
