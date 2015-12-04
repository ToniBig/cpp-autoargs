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

// --- Internal Includes ---
#include "../inc/BooleanArgument.hpp"
#include "../inc/AutoArgsException.hpp"

// --- Std Includes ---
#include <stdexcept>

namespace adhocpp
{
namespace utilities
{

BooleanArgument::BooleanArgument( const std::string& placeHolder,
                                  const std::string& helpText,
                                  bool value ) :
        AbsArgument( placeHolder, helpText ),
        myValue( value )
{
}

BooleanArgument::~BooleanArgument( )
{
}

std::string BooleanArgument::getType( ) const
{
  return "bool";
}

std::string BooleanArgument::getValue( ) const
{
  if ( myValue )
  {
    return "true";
  }
  else
  {
    return "false";
  }
}

void BooleanArgument::setValue( std::string value )
{
  if ( value == "true" || value == "1" )
  {
    myValue = true;
  }
  else if ( value == "false" || value == "0" )
  {
    myValue = false;
  }
  else
  {
    throw std::runtime_error( "Provided incorrect argument value. Allowed values are: 0, 1, true, false." );
  }
}

BooleanArgument::operator bool( ) const
{
  return myValue;
}

bool BooleanArgument::value( ) const
{
  return myValue;
}

bool BooleanArgument::operator *( ) const
{
  return myValue;
}

} // namespace utilities
} // namespace adhocpp
