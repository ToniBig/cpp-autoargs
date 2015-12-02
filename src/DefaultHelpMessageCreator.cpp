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
#include "../inc/DefaultHelpMessageCreator.hpp"

namespace adhocpp
{
namespace utilities
{

const size_t placeHolderWidth = 25;
const size_t typeValueWidth = 32;

DefaultHelpMessageCreator::DefaultHelpMessageCreator( )
{
}

DefaultHelpMessageCreator::~DefaultHelpMessageCreator( )
{
}

std::string DefaultHelpMessageCreator::appendWhiteSpace( const std::string& input,
                                                         size_t finalWidth )
{
    std::string output = input;

    size_t currentWidth = output.size( );

    if ( currentWidth > finalWidth )
    {
      output += "\n\t" + std::string( finalWidth, ' ' );
    }
    else
    {
      size_t difference = finalWidth - currentWidth;

      output += std::string( difference, ' ' );
    }

    return output;
}

std::string DefaultHelpMessageCreator::createUsageBlock( const DriverData& driverData )
{
    std::string description;

    description += "Usage: \n";

    description += driverData.driverName + " ";

    for ( auto& argument : driverData.requiredArguments )
    {
      description += argument.placeHolder + " ";
    }
    description += "[--options]\n";

    description += driverData.driverName + " --input inputFileName\n";


    return description;
}

std::string DefaultHelpMessageCreator::createPurposeBlock( const DriverData& driverData )
{
    std::string description;

    if ( driverData.description.empty( ) == false )
    {
      description += "\nPurpose: \n\n" + driverData.description + "\n";
    }

    return description;
}

std::string DefaultHelpMessageCreator::createArgumentsBlock( const std::vector<adhocpp::utilities::ArgumentData>& arguments,
                                                             const std::string& argumentsType,
                                                             const std::string& prefix )
{
    std::string description;
    if ( arguments.empty( ) == false )
    {
      description += "\n" + argumentsType + ":\n";
      for ( auto& argument : arguments )
      {
        description += "\n\t";
        description += appendWhiteSpace( prefix + argument.placeHolder, placeHolderWidth );

        if ( !argument.type.empty( ) )
        {
          description += " : ";

          if ( argument.defaultValue.empty( ) )
          {
            description += appendWhiteSpace( argument.type, typeValueWidth );
          }
          else
          {
            description += appendWhiteSpace( argument.type + " (" + argument.defaultValue + ")", typeValueWidth );
          }
        }

        description += " : ";
        description += argument.helpText;
      }
      description += "\n";
    }

    return description;
}

std::string DefaultHelpMessageCreator::createRequiredArgumentsBlock( const DriverData& driverData )
{
    auto arguments = driverData.requiredArguments;
    std::string argumentsType( "Required arguments" );

    return createArgumentsBlock( arguments, argumentsType, "" );
}

std::string DefaultHelpMessageCreator::createOptionalArgumentsBlock( const DriverData& driverData )
{
    auto arguments = driverData.optionalArguments;
    std::string argumentsType( "Optional arguments" );

    return createArgumentsBlock( arguments, argumentsType, "--" );
}

std::string DefaultHelpMessageCreator::createBuiltInArgumentsBlock( const DriverData& driverData )
{
    auto arguments = driverData.builtInArguments;
    std::string argumentsType( "Built-In arguments" );

    return createArgumentsBlock( arguments, argumentsType, "--" );
}

std::string DefaultHelpMessageCreator::getHelpMessage( const DriverData& driverData )
{
    std::string description;

    // Usage

    description += createUsageBlock( driverData );

    // Purpose

    description += createPurposeBlock( driverData );

    // Required arguments

    description += createRequiredArgumentsBlock( driverData );

    // Optional Arguments

    description += createOptionalArgumentsBlock( driverData );

    // Built-In Arguments

    description += createBuiltInArgumentsBlock( driverData );

    return description;
}

} // namespace utilities
} // namespace adhocpp
