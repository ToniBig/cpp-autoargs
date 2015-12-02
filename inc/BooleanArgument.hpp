/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_BOOLEANARGUMENT_HPP_
#define UTILITIES_BOOLEANARGUMENT_HPP_

// --- Internal Includes ---
#include "AbsArgument.hpp"

namespace adhocpp
{
namespace utilities
{

class BooleanArgument : public AbsArgument
{
public:
  BooleanArgument( const std::string& placeHolder,
                   const std::string& helpText );

  BooleanArgument( const std::string& placeHolder,
                   const std::string& helpText,
                   bool defaultValue );

  virtual ~BooleanArgument( );

  std::string getType( ) const;

  std::string getDefaultValue( ) const;

  void setValue( std::string value );

  operator bool( ) const;

  bool value( ) const;

private:
  explicit BooleanArgument( const BooleanArgument& );
  BooleanArgument& operator=( const BooleanArgument& );

  bool myDefaultValue;
};

} // namespace utilities
} // namespace adhocpp
#endif // UTILITIES_BOOLEANARGUMENT_HPP_
