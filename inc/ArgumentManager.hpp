/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_ARGUMENTMANAGER_HPP_
#define UTILITIES_ARGUMENTMANAGER_HPP_

// --- Internal Includes ---
#include "AbsArgument.hpp"
#include "DriverData.hpp"

// --- Standard Includes ---
#include <map>
#include <vector>

namespace adhocpp
{
namespace utilities
{

typedef std::vector<std::string> StringVector;
typedef std::map<std::string, std::string> PlaceHolderValueMap;

class ArgumentManager
{
public:
  ~ArgumentManager( );

  static ArgumentManager& getInstance( );

  void clear( );

  void registerArgument( AbsArgument& argument );

  void unregisterArgument( AbsArgument& argument );

  size_t getNumberOfOptionalArguments( ) const;

  size_t getNumberOfRequiredArguments( ) const;

  void setRequiredArguments( StringVector argumentValues );

  void setOptionalArguments( StringVector argumentValues );

  void setArguments( PlaceHolderValueMap placeHoldersAndValues );

  DriverData getDriverData( ) const;

private:
  ArgumentManager( );
  explicit ArgumentManager( const ArgumentManager& );
  ArgumentManager& operator=( const ArgumentManager& );

  bool isOptional( std::string argument ) const;

  void addDefaultArgument( AbsArgument* argument );

  void addRequiredArgument( AbsArgument* argument );

  typedef std::map<std::string,AbsArgument*> StringArgumentMap;
  typedef std::vector<AbsArgument*> ArgumentVector;

  StringArgumentMap myOptionalArguments;
  ArgumentVector myRequiredArguments;
};

} // namespace utilities
} // namespace adhocpp
#endif // UTILITIES_ARGUMENTMANAGER_HPP_
