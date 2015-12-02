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
#include "../inc/AbsArgument.hpp"
#include "../inc/ArgumentManager.hpp"

namespace adhocpp
{
namespace utilities
{

AbsArgument::AbsArgument( const std::string& placeHolder,
                          const std::string& helpText,
                          bool defaultValueState ) :
        myPlaceHolder( placeHolder ),
        myHelpText( helpText ),
        myDefaultValueState( defaultValueState )
{
    ArgumentManager::getInstance( ).registerArgument( *this );
}

AbsArgument::~AbsArgument( )
{
  try
  {
    ArgumentManager::getInstance( ).unregisterArgument( *this );
  }
  catch ( ... )
  {
  }
}

std::string AbsArgument::getPlaceHolder( ) const
{
    return myPlaceHolder;
}

std::string AbsArgument::getHelpText( ) const
{
    return myHelpText;
}

bool AbsArgument::hasDefaultValue( ) const
{
    return myDefaultValueState;
}

} // namespace utilities
} // namespace adhocpp
