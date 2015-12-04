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

#ifndef AUTOARGS_STRINGARGUMENT_HPP_
#define AUTOARGS_STRINGARGUMENT_HPP_

// --- Internal Includes ---
#include "AbsArgument.hpp"

namespace autoargs
{

class StringArgument : public AbsArgument
{
public:
  StringArgument( const std::string& placeHolder,
                  const std::string& helpText,
                  const std::string& value );

  virtual ~StringArgument( );

  std::string getType( ) const;

  std::string getValue( ) const;

  void setValue( std::string value );

  operator std::string( ) const;

  std::string value( ) const;

  std::string operator*( ) const;

private:
  explicit StringArgument( const StringArgument& );
  StringArgument& operator=( const StringArgument& );

  std::string myValue;
};

} // namespace autoargs
#endif // AUTOARGS_STRINGARGUMENT_HPP_
