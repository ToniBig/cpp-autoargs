/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_AUTOARGSEXCEPTION_HPP_
#define UTILITIES_AUTOARGSEXCEPTION_HPP_

// --- Standard Includes ---
#include <exception>
#include <memory>
#include <string>

namespace adhocpp
{
namespace utilities
{

class AutoArgsException : public std::exception
{
public:
  explicit AutoArgsException( const std::string& message );
  explicit AutoArgsException( const AutoArgsException& exception );

  virtual ~AutoArgsException( ) throw ( );

  const char* what( ) const throw ( );

private:
  std::string message;
  std::unique_ptr<bool> whatNotCalled;
};

} // namespace utilities
} // namespace adhocpp
#endif // UTILITIES_AUTOARGSEXCEPTION_HPP_
