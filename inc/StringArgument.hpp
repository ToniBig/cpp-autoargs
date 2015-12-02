/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_STRINGARGUMENT_HPP_
#define UTILITIES_STRINGARGUMENT_HPP_

// --- Internal Includes ---
#include "AbsArgument.hpp"

namespace adhocpp
{
namespace utilities
{

class StringArgument : public AbsArgument
{
public:
  StringArgument( const std::string& placeHolder,
                  const std::string& helpText );

  StringArgument( const std::string& placeHolder,
                  const std::string& helpText,
                  const std::string& defaultValue );

  virtual ~StringArgument( );

  std::string getType( ) const;

  std::string getDefaultValue( ) const;

  void setValue( std::string value );

  operator std::string( ) const;

  std::string value( ) const;

private:
  explicit StringArgument( const StringArgument& );
  StringArgument& operator=( const StringArgument& );

  std::string myDefaultValue;
};

} // namespace utilities
} // namespace adhocpp
#endif // UTILITIES_STRINGARGUMENT_HPP_
