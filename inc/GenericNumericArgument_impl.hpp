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

// --- Standard Includes ---
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <type_traits>

namespace autoargs
{

template<typename T>
struct TypeTag
{
};

struct TypeToStringHelper
{
  static std::string typeToString( TypeTag<double> )
  {
    return "double";
  }

  static std::string typeToString( TypeTag<float> )
  {
    return "float";
  }

  static std::string typeToString( TypeTag<size_t> )
  {
    return "size_t";
  }

  static std::string typeToString( TypeTag<int> )
  {
    return "int";
  }

  static std::string typeToString( TypeTag<short> )
  {
    return "short";
  }
};

template<typename T>
inline GenericNumericArgument<T>::GenericNumericArgument( const std::string& placeHolder,
                                                          const std::string& helpText,
                                                          T defaultValue ) :
        AbsArgument( placeHolder, helpText ),
        myValue( defaultValue )
{
}

template<typename T>
inline GenericNumericArgument<T>::~GenericNumericArgument( )
{
}

template<typename T>
inline std::string GenericNumericArgument<T>::getType( ) const
{
  return TypeToStringHelper::typeToString( TypeTag<T>( ) );
}

template<typename T>
inline std::string GenericNumericArgument<T>::getValue( ) const
{
  if ( std::is_floating_point < T > ::value )
  {
    std::stringstream stream;
    stream << std::setprecision( 15 ) << std::scientific << myValue;
    return stream.str( );
  }
  else
  {
    return std::to_string( myValue );
  }
}

template<typename T>
inline void GenericNumericArgument<T>::setValue( std::string value )
{
  std::istringstream inputStream;
  inputStream.str( value );

  inputStream >> myValue;
}

template<typename T>
inline GenericNumericArgument<T>::operator T( ) const
{
  return this->value( );
}

template<typename T>
inline T GenericNumericArgument<T>::value( ) const
{
  return myValue;
}

template<typename T>
inline T GenericNumericArgument<T>::operator *( ) const
{
  return this->value( );
}

} // namespace autoargs
