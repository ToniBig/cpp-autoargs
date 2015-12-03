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

#ifndef AUTOARGS_GENERICARGUMENTPARSER_HPP_
#define AUTOARGS_GENERICARGUMENTPARSER_HPP_

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

#endif // AUTOARGS_GENERICARGUMENTPARSER_HPP_
