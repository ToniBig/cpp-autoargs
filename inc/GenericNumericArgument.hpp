/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_GENERICNUMERICARGUMENT_HPP_
#define UTILITIES_GENERICNUMERICARGUMENT_HPP_

// --- Internal Includes ---
#include "AbsArgument.hpp"

namespace adhocpp
{
namespace utilities
{

template<typename T>
class GenericNumericArgument : public AbsArgument
{
public:
  GenericNumericArgument( const std::string& placeHolder,
                          const std::string& helpText );

  GenericNumericArgument( const std::string& placeHolder,
                          const std::string& helpText,
                          T defaultValue );

  virtual ~GenericNumericArgument( );

  std::string getType( ) const;

  std::string getDefaultValue( ) const;

  void setValue( std::string value );

  operator T( ) const;

  T value( ) const;

  T operator*( ) const;

private:
  explicit GenericNumericArgument( const GenericNumericArgument& );
  GenericNumericArgument& operator=( const GenericNumericArgument& );

  T myDefaultValue;
};

} // namespace utilities
} // namespace adhocpp

#include "GenericNumericArgument_impl.hpp"

#endif // UTILITIES_GENERICNUMERICARGUMENT_HPP_
