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

#ifndef AUTOARGS_AUTOARGSEXCEPTION_HPP_
#define AUTOARGS_AUTOARGSEXCEPTION_HPP_

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
#endif // AUTOARGS_AUTOARGSEXCEPTION_HPP_
