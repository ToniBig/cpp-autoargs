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
#include "../inc/ArgumentManager.hpp"
#include "../inc/AutoArgsException.hpp"

// --- Standard Includes ---
#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace adhocpp {
namespace utilities {

ArgumentManager& ArgumentManager::getInstance( )
{
    static ArgumentManager myInstance; // Meyers Singleton

    return myInstance;
}

void ArgumentManager::addDefaultArgument( AbsArgument* argument )
{
    bool alreadyDefined = myOptionalArguments.count( argument->getPlaceHolder( ) ) != 0;

    if ( alreadyDefined )
    {
      throw std::runtime_error( "Optional Argument " + argument->getPlaceHolder( ) + " has already been defined!" );
    }
    else
    {
      myOptionalArguments[argument->getPlaceHolder( )] = argument;
    }
}

size_t ArgumentManager::getNumberOfOptionalArguments( ) const
{
    return myOptionalArguments.size( );
}

size_t ArgumentManager::getNumberOfRequiredArguments( ) const
{
    return myRequiredArguments.size( );
}

void ArgumentManager::clear( )
{
    myOptionalArguments.clear( );
    myRequiredArguments.clear( );
}

void ArgumentManager::setRequiredArguments( StringVector argumentValues )
{
    for ( size_t iArgument = 0; iArgument < myRequiredArguments.size( ); ++iArgument )
    {
      std::string currentArgument = argumentValues.at( iArgument );

      if ( isOptional( currentArgument ) )
      {
        throw std::runtime_error( "Argument is optional: " + currentArgument + ". Should be required!" );
      }

      myRequiredArguments.at( iArgument )->setValue( currentArgument );
    } // end of iArgument-loop
}

void ArgumentManager::setOptionalArguments( StringVector argumentValues )
{
    for ( size_t iArgument = 0; iArgument < argumentValues.size( ); ++iArgument )
    {
      std::string currentArgument = argumentValues[iArgument];

      if ( isOptional( currentArgument ) )
      {
        size_t pos = currentArgument.find( '=' );

        std::string placeHolder = currentArgument.substr( 2, pos - 2 );
        std::string value = currentArgument.substr( pos + 1, currentArgument.size( ) );

        if ( myOptionalArguments.count( placeHolder ) == 0 )
        {
          throw std::runtime_error( "Argument not found: " + placeHolder );
        }

        myOptionalArguments[placeHolder]->setValue( value );
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

    for ( const auto& argument : myRequiredArguments )
    {
      data.requiredArguments.push_back(
          makeArgument( argument->getPlaceHolder( ), argument->getHelpText( ), argument->getType( ), argument->getDefaultValue( ) ) );
    } // end of argument-loop

    for ( const auto& argument : myOptionalArguments )
    {
      data.optionalArguments.push_back(
          makeArgument( argument.second->getPlaceHolder( ), argument.second->getHelpText( ), argument.second->getType( ),
              argument.second->getDefaultValue( ) ) );
    } // end of argument-loop

    return data;
}

void ArgumentManager::addRequiredArgument( AbsArgument* argument )
{
    auto iter = std::find( myRequiredArguments.begin( ), myRequiredArguments.end( ), argument );

    if ( iter == myRequiredArguments.end( ) || myRequiredArguments.empty( ) )
    {
      myRequiredArguments.push_back( argument );
    }
    else
    {
      throw std::runtime_error( "Required Argument " + argument->getPlaceHolder( ) + " has already been defined!" );
    }
}

void ArgumentManager::registerArgument( AbsArgument& argument )
{
    if ( argument.hasDefaultValue( ) )
    {
      addDefaultArgument( &argument );
    }
    else
    {
      addRequiredArgument( &argument );
    }
}

void ArgumentManager::unregisterArgument( AbsArgument& argument )
{
    auto isInMap = [&](AbsArgument& argument)
    {
      return (myOptionalArguments.count( argument.getPlaceHolder() ) == 1);
    };

    auto vectorIter = std::find( myRequiredArguments.begin( ), myRequiredArguments.end( ), &argument );

    auto isInVector = [&](AbsArgument& argument)
    {
      return (vectorIter != myRequiredArguments.end( ));
    };

    if ( isInVector( argument ) )
    {
      myRequiredArguments.erase( vectorIter );
    }
    else if ( isInMap( argument ) )
    {
      auto mapIter = myOptionalArguments.find( argument.getPlaceHolder( ) );
      myOptionalArguments.erase( mapIter );
    }
    else
    {
      throw std::runtime_error( "Argument " + argument.getPlaceHolder( ) + " has never been registered!" );
    }
}

void ArgumentManager::setArguments( PlaceHolderValueMap placeHoldersAndValues )
{
  for ( PlaceHolderValueMap::iterator iterator = placeHoldersAndValues.begin( ); iterator != placeHoldersAndValues.end( ); ++iterator )
  {
    auto placeHolder = iterator->first;
    auto value = iterator->second;

    // Look into required arguments
    for ( auto argument : myRequiredArguments )
    {
      if ( argument->getPlaceHolder( ) == placeHolder )
      {
        argument->setValue( value );
        break;
      }
    }

    // Look into optional arguments
    for ( StringArgumentMap::iterator optionalIterator = myOptionalArguments.begin( ); optionalIterator != myOptionalArguments.end( );
        ++optionalIterator )
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

