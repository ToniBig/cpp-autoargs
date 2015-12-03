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

#ifndef AUTOARGS_DRIVERDATA_HPP_
#define AUTOARGS_DRIVERDATA_HPP_

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
#endif // AUTOARGS_DRIVERDATA_HPP_
