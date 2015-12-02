/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\____//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_DRIVERDATA_HPP_
#define UTILITIES_DRIVERDATA_HPP_

// --- Standard Includes ---
#include <string>
#include <vector>

namespace adhocpp
{
namespace utilities
{

struct ArgumentData
{
  std::string placeHolder;
  std::string helpText;
  std::string type;
  std::string defaultValue;
};

struct DriverData
{
  std::string driverName;
  std::string description;
  std::vector<ArgumentData> builtInArguments;
  std::vector<ArgumentData> requiredArguments;
  std::vector<ArgumentData> optionalArguments;
};

inline ArgumentData makeArgument( const std::string& placeholder,
                                  const std::string& helpText )
{
  ArgumentData data = { placeholder, helpText, { }, { } };

  return data;
}

inline ArgumentData makeArgument( const std::string& placeholder,
                                          const std::string& helpText,
                                          const std::string& type )
{
  ArgumentData data = { placeholder, helpText, type, { } };

  return data;
}

inline ArgumentData makeArgument( const std::string& placeholder,
                                                    const std::string& helpText,
                                                    const std::string& type,
                                                    const std::string& defaulValue )
{
  ArgumentData data = { placeholder, helpText, type, defaulValue };

  return data;
}

} // namespace utilities
} // namespace adhocpp
#endif // UTILITIES_DRIVERDATA_HPP_
