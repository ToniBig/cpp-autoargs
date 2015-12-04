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
#include "../inc/DefaultHelpMessageCreator.hpp"

namespace autoargs
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

std::string DefaultHelpMessageCreator::createArgumentsBlock( const std::vector<ArgumentData>& arguments,
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

  // Optional Arguments

  description += createOptionalArgumentsBlock( driverData );

  // Built-In Arguments

  description += createBuiltInArgumentsBlock( driverData );

  return description;
}

} // namespace autoargs

