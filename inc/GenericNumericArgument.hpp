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
