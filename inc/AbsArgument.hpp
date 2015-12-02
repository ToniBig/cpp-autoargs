/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_ABSARGUMENT_HPP_
#define UTILITIES_ABSARGUMENT_HPP_

// --- Standard Includes ---
#include <string>

namespace adhocpp
{
namespace utilities
{

class AbsArgument
{
public:
  AbsArgument( const std::string& placeHolder,
               const std::string& helpText,
               bool defaultValueState );

  virtual ~AbsArgument( );

  std::string getPlaceHolder( ) const;
  std::string getHelpText( ) const;
  bool hasDefaultValue( ) const;

  virtual std::string getType( ) const = 0;
  virtual std::string getDefaultValue( ) const = 0;

  virtual void setValue( std::string value ) = 0;

private:
  explicit AbsArgument( const AbsArgument& );
  AbsArgument& operator=( const AbsArgument& );

  std::string myPlaceHolder;
  std::string myHelpText;

protected:
  bool myDefaultValueState;
};

} // namespace utilities
} // namespace adhocpp
#endif // UTILITIES_ABSARGUMENT_HPP_
