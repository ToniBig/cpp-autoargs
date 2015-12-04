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

#ifndef AUTOARGS_ARGUMENTMANAGER_HPP_
#define AUTOARGS_ARGUMENTMANAGER_HPP_

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

  size_t getNumberOfArguments( ) const;

  void setArguments( StringVector argumentValues );

  void setArguments( PlaceHolderValueMap placeHoldersAndValues );

  DriverData getDriverData( ) const;

private:
  ArgumentManager( );
  explicit ArgumentManager( const ArgumentManager& );
  ArgumentManager& operator=( const ArgumentManager& );

  bool isOptional( std::string argument ) const;

  void addDefaultArgument( AbsArgument* argument );

  typedef std::map<std::string, AbsArgument*> StringArgumentMap;
  typedef std::vector<AbsArgument*> ArgumentVector;

  StringArgumentMap myArguments;
};

} // namespace utilities
} // namespace adhocpp
#endif // AUTOARGS_ARGUMENTMANAGER_HPP_
