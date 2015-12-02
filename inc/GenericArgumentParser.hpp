/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_GENERICARGUMENTPARSER_HPP_
#define UTILITIES_GENERICARGUMENTPARSER_HPP_

// --- Internal Includes ---
#include "../inc/DriverData.hpp"

// --- Standard Includes ---
#include <string>

namespace adhocpp {
namespace utilities {

struct AdhocppExceptionPolicy
{
  static void error( std::string message );
};

struct CoutAndExitPolicy
{
  static void error( std::string message );
};

// TODO (bog Nov 26, 2013): Add file parser for option --i (xml, json, etc.)
template<typename HelpMessagePolicy, typename ErrorPolicy, typename InputFilePolicy>
class GenericArgumentParser : public HelpMessagePolicy, public ErrorPolicy, public InputFilePolicy
{
public:
  static void parseCommandLine( int argc,
                                char **argv );

  static void setDriverDescription( const std::string& driverDescription );

  static std::string listArguments( );

private:
  explicit GenericArgumentParser( const GenericArgumentParser& );
  GenericArgumentParser& operator=( const GenericArgumentParser& );

  static void createInputFile( const std::string& driverName );

  static void processArguments( const std::vector<ArgumentData>& arguments,
                                std::ostringstream& listOfArguments );

  static std::string description;
};

} // namespace utilities
} // namespace adhocpp

#include "GenericArgumentParser_impl.hpp"

#endif // UTILITIES_GENERICARGUMENTPARSER_HPP_
