/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_DEFAULTHELPMESSAGECREATOR_HPP_
#define UTILITIES_DEFAULTHELPMESSAGECREATOR_HPP_

// --- Internal Includes ---
#include "DriverData.hpp"

// --- Standard Includes ---
#include <string>

namespace adhocpp
{
namespace utilities
{

class DefaultHelpMessageCreator
{
public:
  DefaultHelpMessageCreator( );
  virtual ~DefaultHelpMessageCreator( );

  static std::string getHelpMessage( const DriverData& driverData );

private:
  explicit DefaultHelpMessageCreator( const DefaultHelpMessageCreator& );
  DefaultHelpMessageCreator& operator=( const DefaultHelpMessageCreator& );

  static std::string createUsageBlock( const DriverData& driverData );

  static std::string createPurposeBlock( const DriverData& driverData );

  static std::string createRequiredArgumentsBlock( const DriverData& driverData );

  static std::string createOptionalArgumentsBlock( const DriverData& driverData );

  static std::string createBuiltInArgumentsBlock( const DriverData& driverData );

  static std::string appendWhiteSpace( const std::string& input,
                                       size_t finalWidth );

  static std::string createArgumentsBlock( const std::vector<adhocpp::utilities::ArgumentData>& arguments,
                                           const std::string& argumentsType,
                                           const std::string& prefix );
};

} // namespace utilities
} // namespace adhocpp
#endif // UTILITIES_DEFAULTHELPMESSAGECREATOR_HPP_
