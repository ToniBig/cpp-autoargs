/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

// --- Standard Includes ---
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <type_traits>

namespace adhocpp
{
namespace utilities
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
                                                          const std::string& helpText ) :
        AbsArgument( placeHolder, helpText, false )
{
}

template<typename T>
inline GenericNumericArgument<T>::GenericNumericArgument( const std::string& placeHolder,
                                                          const std::string& helpText,
                                                          T defaultValue ) :
        AbsArgument( placeHolder, helpText, true ),
        myDefaultValue( defaultValue )
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
inline std::string GenericNumericArgument<T>::getDefaultValue( ) const
{
  if ( std::is_floating_point<T>::value )
  {
    std::stringstream stream;
    stream << std::setprecision( 15 ) << std::scientific << myDefaultValue;
    return stream.str( );
  }
  else
  {
    return std::to_string( myDefaultValue );
  }
}

template<typename T>
inline void GenericNumericArgument<T>::setValue( std::string value )
{
  std::istringstream inputStream;
  inputStream.str( value );

  inputStream >> myDefaultValue;

  myDefaultValueState = true;
}

template<typename T>
inline GenericNumericArgument<T>::operator T( ) const
{
  return this->value( );
}

template<typename T>
inline T GenericNumericArgument<T>::value( ) const
{
  if ( hasDefaultValue( ) )
  {
    return myDefaultValue;
  }
  else
  {
    throw std::runtime_error( "No default value specified for: " + this->getPlaceHolder( ) );
  }
}

template<typename T>
inline T adhocpp::utilities::GenericNumericArgument<T>::operator *( ) const
{
  return this->value( );
}

} // namespace utilities
} // namespace adhocpp
