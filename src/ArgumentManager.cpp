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
#include "../inc/ArgumentManager.hpp"
#include "../inc/AutoArgsException.hpp"

// --- Standard Includes ---
#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace adhocpp
{
namespace utilities
{

ArgumentManager& ArgumentManager::getInstance( )
{
  static ArgumentManager myInstance; // Meyers Singleton

  return myInstance;
}

void ArgumentManager::addDefaultArgument( AbsArgument* argument )
{
  bool alreadyDefined = myArguments.count( argument->getPlaceHolder( ) ) != 0;

  if ( alreadyDefined )
  {
    throw std::runtime_error( "Optional Argument " + argument->getPlaceHolder( ) + " has already been defined!" );
  }
  else
  {
    myArguments[argument->getPlaceHolder( )] = argument;
  }
}

size_t ArgumentManager::getNumberOfArguments( ) const
{
  return myArguments.size( );
}

void ArgumentManager::clear( )
{
  myArguments.clear( );
}

void ArgumentManager::setArguments( StringVector argumentValues )
{
  for ( size_t iArgument = 0; iArgument < argumentValues.size( ); ++iArgument )
  {
    std::string currentArgument = argumentValues[iArgument];

    if ( isOptional( currentArgument ) )
    {
      size_t pos = currentArgument.find( '=' );

      std::string placeHolder = currentArgument.substr( 2, pos - 2 );
      std::string value = currentArgument.substr( pos + 1, currentArgument.size( ) );

      if ( myArguments.count( placeHolder ) == 0 )
      {
        throw std::runtime_error( "Argument not found: " + placeHolder );
      }

      myArguments[placeHolder]->setValue( value );
    }
    else
    {
      throw std::runtime_error( "Argument is not optional: " + currentArgument );
    }

  } // end of iArgument-loop
}

bool ArgumentManager::isOptional( std::string argument ) const
{
  bool hasDash = ( argument[0] == '-' && argument[1] == '-' );

  size_t pos = argument.find( '=' );

  bool hasAssignment = pos != std::string::npos;

  return ( hasDash && hasAssignment );
}

DriverData ArgumentManager::getDriverData( ) const
{
  DriverData data;

  for ( const auto& argument : myArguments )
  {
    data.optionalArguments.push_back( makeArgument( argument.second->getPlaceHolder( ), argument.second->getHelpText( ), argument.second->getType( ), argument.second->getValue( ) ) );
  } // end of argument-loop

  return data;
}

void ArgumentManager::registerArgument( AbsArgument& argument )
{
  addDefaultArgument( &argument );
}

void ArgumentManager::unregisterArgument( AbsArgument& argument )
{
  auto isInMap = [&](AbsArgument& argument)
  {
    return (myArguments.count( argument.getPlaceHolder() ) == 1);
  };
}

void ArgumentManager::setArguments( PlaceHolderValueMap placeHoldersAndValues )
{
  for ( PlaceHolderValueMap::iterator iterator = placeHoldersAndValues.begin( ); iterator != placeHoldersAndValues.end( ); ++iterator )
  {
    auto placeHolder = iterator->first;
    auto value = iterator->second;

    // Look into optional arguments
    for ( StringArgumentMap::iterator optionalIterator = myArguments.begin( ); optionalIterator != myArguments.end( ); ++optionalIterator )
    {
      if ( optionalIterator->first == placeHolder )
      {
        optionalIterator->second->setValue( value );
        break;
      }
    } // end of optionalIterator-loop

  } // end of iterator-loop
}

ArgumentManager::ArgumentManager( )
{
}

ArgumentManager::~ArgumentManager( )
{
}

} // namespace utilities
} // namespace adhocpp

