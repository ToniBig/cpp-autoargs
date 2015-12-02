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

// --- Standard Includes ---
#include <stdexcept>

namespace adhocpp
{
namespace utilities
{

StringArgument::StringArgument( const std::string& placeHolder,
                                const std::string& helpText ) :
        AbsArgument( placeHolder, helpText, false )
{
}

StringArgument::StringArgument( const std::string& placeHolder,
                                const std::string& helpText,
                                const std::string& defaultValue ) :
        AbsArgument( placeHolder, helpText, true ),
        myDefaultValue( defaultValue )
{
}

StringArgument::~StringArgument( )
{
}

std::string StringArgument::getType( ) const
{
    return "string";
}

std::string StringArgument::getDefaultValue( ) const
{
    return myDefaultValue;
}

void StringArgument::setValue( std::string value )
{
    myDefaultValue = value;

    myDefaultValueState = true;
}

StringArgument::operator std::string( ) const
{
    return this->value( );
}

std::string StringArgument::value( ) const
{
    if ( hasDefaultValue( ) )
    {
      return myDefaultValue;
    }
    else
    {
      throw std::runtime_error( "No default value specified for: " + this->getPlaceHolder( ) );
    }
}

} // namespace utilities
} // namespace adhocpp
