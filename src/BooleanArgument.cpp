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
#include "../inc/AutoArgsException.hpp"

// --- Std Includes ---
#include <stdexcept>

namespace adhocpp
{
namespace utilities
{

BooleanArgument::BooleanArgument( const std::string& placeHolder,
                                  const std::string& helpText ) :
        AbsArgument( placeHolder, helpText, true ),
        myDefaultValue( false )
{
}

BooleanArgument::BooleanArgument( const std::string& placeHolder,
                                  const std::string& helpText,
                                  bool defaultValue ) :
        AbsArgument( placeHolder, helpText, true ),
        myDefaultValue( defaultValue )
{
}

BooleanArgument::~BooleanArgument( )
{
}

std::string BooleanArgument::getType( ) const
{
    return "bool";
}

std::string BooleanArgument::getDefaultValue( ) const
{
    if ( myDefaultValue )
    {
      return "true";
    }
    else
    {
      return "false";
    }
}

void BooleanArgument::setValue( std::string value )
{
    if ( value == "true" || value == "1" )
    {
      myDefaultValue = true;
    }
    else if ( value == "false" || value == "0" )
    {
      myDefaultValue = false;
    }
    else
    {
      throw std::runtime_error( "Provided incorrect argument value. Allowed values are: 0, 1, true, false." );
    }

    myDefaultValueState = true;
}

BooleanArgument::operator bool( ) const
{
    return myDefaultValue;
}

bool BooleanArgument::value( ) const
{
    return myDefaultValue;
}

} // namespace utilities
} // namespace adhocpp
