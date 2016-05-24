// The MIT License (MIT)
//
// Copyright (c) 2013-2016 Tino Bog
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

#ifndef _AUTOARGS_HPP_
#define _AUTOARGS_HPP_

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace autoargs {

template<typename T>
struct GenericArgument;

using BoolArg = GenericArgument<bool>;
using StringArg = GenericArgument<std::string>;

using FloatArg = GenericArgument<float>;
using DoubleArg = GenericArgument<double>;
using LongDoubleArg = GenericArgument<long double>;

using IntArg = GenericArgument<int>;
using UnsignedIntArg = GenericArgument<unsigned int>;
using ShortArg = GenericArgument<short>;
using UnsignedShortArg = GenericArgument<unsigned short>;
using LongArg = GenericArgument<long>;
using UnsignedLongArg = GenericArgument<unsigned long>;
using SizeArg = GenericArgument<size_t>;

template<typename HelpMessageCreator, typename ErrorPolicy, typename InputFileReaderPolycy>
struct GenericArgumentParser;

struct DefaultHelpMessageCreator;
struct CoutAndExitPolicy;
struct ExceptionPolicy;
struct DefaultInputFileReader;

using ArgumentParser = GenericArgumentParser<DefaultHelpMessageCreator, CoutAndExitPolicy, DefaultInputFileReader>;
using TestArgumentParser = GenericArgumentParser<DefaultHelpMessageCreator, ExceptionPolicy, DefaultInputFileReader>;

namespace detail {

template<typename T>
struct type_traits;

template<>
struct type_traits<float>
{
  static constexpr const char *type = "float";
};

template<>
struct type_traits<double>
{
  static constexpr const char *type = "double";
};

template<>
struct type_traits<long double>
{
  static constexpr const char *type = "long double";
};

template<>
struct type_traits<int>
{
  static constexpr const char *type = "int";
};

template<>
struct type_traits<unsigned int>
{
  static constexpr const char *type = "unsigned int";
};

template<>
struct type_traits<short>
{
  static constexpr const char *type = "short";
};

template<>
struct type_traits<unsigned short>
{
  static constexpr const char *type = "unsigned short";
};

template<>
struct type_traits<long>
{
  static constexpr const char *type = "long";
};

template<>
struct type_traits<unsigned long>
{
  static constexpr const char *type = "unsigned long";
};

template<>
struct type_traits<std::string>
{
  static constexpr const char *type = "string";
};

template<>
struct type_traits<bool>
{
  static constexpr const char *type = "bool";
};

inline std::string to_string( std::string str )
{
  return std::move( str );
}

template<typename T>
std::string to_string( T const &value )
{
  if ( std::is_floating_point<T>::value )
  {
    std::stringstream stream;
    stream << std::setprecision( 15 ) << std::scientific << value;
    return stream.str( );
  }
  else
  {
    return std::to_string( value );
  }
}

inline std::string to_lower( std::string const &str )
{
  std::string lower;
  lower.resize( str.size( ) );

  std::transform( str.begin( ), str.end( ), lower.begin( ), ::tolower );

  return lower;
}

template<typename T>
struct lexical_cast_impl
{
  static T lexical_cast( std::string const &str )
  {
    T value;

    std::istringstream inputStream;
    inputStream.str( str );

    inputStream >> value;

    return value;
  }
};

template<>
struct lexical_cast_impl<bool>
{
  static bool lexical_cast( std::string const &str )
  {
    return ( str == "1" || to_lower( str ) == "true" );
  }
};

template<typename T>
T lexical_cast( std::string const &str )
{
  return lexical_cast_impl<T>::lexical_cast( str );
}

} // namespace detail

class AutoArgsException : public std::exception
{
public:
  explicit AutoArgsException( const std::string& message ) :
          myMessage( message ),
          whatNotCalled( true )

  {
  }

  virtual ~AutoArgsException( ) throw ( )
  {
    try
    {
      if ( whatNotCalled )
      {
        std::cout << "Error: " << myMessage << std::endl;
      }
    }
    catch ( ... )
    {
    }
  }

  const char* what( ) const throw ( )
  {
    whatNotCalled = false;
    return myMessage.c_str( );
  }

private:
  std::string myMessage;
  mutable bool whatNotCalled;
};

namespace detail {
inline void check( bool predicate,
                   std::string&& message )
{
  if ( not predicate )
  {
    throw AutoArgsException( message );
  }
}
} // namespace detail

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

class AbsArgument
{
public:
  AbsArgument( const std::string& placeHolder,
               const std::string& helpText ) :
          myPlaceHolder( placeHolder ),
          myHelpText( helpText )
  {
  }

  virtual ~AbsArgument( )
  {
  }

  explicit AbsArgument( const AbsArgument& ) = delete;
  AbsArgument& operator=( const AbsArgument& ) = delete;

  std::string getPlaceHolder( ) const
  {
    return myPlaceHolder;
  }

  std::string getHelpText( ) const
  {
    return myHelpText;
  }

  virtual std::string getType( ) const = 0;
  virtual std::string getValue( ) const = 0;

  virtual void setValue( std::string value ) = 0;

private:
  std::string myPlaceHolder;
  std::string myHelpText;
};

using StringVector = std::vector<std::string>;
using PlaceHolderValueMap = std::map<std::string, std::string>;

class ArgumentManager
{
public:
  static void clear( )
  {
    ArgumentManager::getInstance( ).myArguments.clear( );
  }

  static void registerArgument( AbsArgument& argument )
  {
    ArgumentManager::getInstance( ).addDefaultArgument( &argument );
  }

  static size_t getNumberOfArguments( )
  {
    return ArgumentManager::getInstance( ).myArguments.size( );
  }

  static void setArguments( StringVector argumentValues )
  {
    for ( const auto & currentArgument : argumentValues )
    {
      detail::check( ArgumentManager::getInstance( ).isOptional( currentArgument ), "Argument is not optional: " + currentArgument );

      size_t pos = currentArgument.find( '=' );

      std::string placeHolder = currentArgument.substr( 2, pos - 2 );
      std::string value = currentArgument.substr( pos + 1, currentArgument.size( ) );

      detail::check( ArgumentManager::getInstance( ).myArguments.count( placeHolder ), "Argument not found: " + placeHolder );

      ArgumentManager::getInstance( ).myArguments[placeHolder]->setValue( value );

    } // end of currentArgument-loop
  }

  static void setArguments( PlaceHolderValueMap placeHoldersAndValues )
  {
    for ( PlaceHolderValueMap::iterator iterator = placeHoldersAndValues.begin( ); iterator != placeHoldersAndValues.end( ); ++iterator )
    {
      auto placeHolder = iterator->first;
      auto value = iterator->second;

      // Look into optional arguments
      for ( StringArgumentMap::iterator optionalIterator = ArgumentManager::getInstance( ).myArguments.begin( ); optionalIterator != ArgumentManager::getInstance( ).myArguments.end( );
          ++optionalIterator )
      {
        if ( optionalIterator->first == placeHolder )
        {
          optionalIterator->second->setValue( value );
          break;
        }
      } // end of optionalIterator-loop

    } // end of iterator-loop
  }

  static DriverData getDriverData( )
  {
    DriverData data;

    for ( const auto& argument : ArgumentManager::getInstance( ).myArguments )
    {
      data.optionalArguments.push_back( makeArgument( argument.second->getPlaceHolder( ), argument.second->getHelpText( ), argument.second->getType( ), argument.second->getValue( ) ) );
    } // end of argument-loop

    return data;
  }

private:
  ArgumentManager( )
  {
  }

  static ArgumentManager& getInstance( )
  {
    static ArgumentManager myInstance; // Meyers Singleton

    return myInstance;
  }

  explicit ArgumentManager( const ArgumentManager& );
  ArgumentManager& operator=( const ArgumentManager& );

  bool isOptional( std::string argument ) const
  {
    bool hasDash = ( argument[0] == '-' && argument[1] == '-' );

    size_t pos = argument.find( '=' );

    bool hasAssignment = pos != std::string::npos;

    return ( hasDash && hasAssignment );
  }

  void addDefaultArgument( AbsArgument* argument )
  {
    detail::check( myArguments.count( argument->getPlaceHolder( ) ) == 0, "Optional Argument " + argument->getPlaceHolder( ) + " has already been defined!" );

    myArguments[argument->getPlaceHolder( )] = argument;
  }

  using StringArgumentMap = std::map<std::string, AbsArgument*>;
  using ArgumentVector = std::vector<AbsArgument*>;

  StringArgumentMap myArguments;
};

template<typename T>
class GenericArgument : public AbsArgument
{
public:
  GenericArgument( std::string const &placeHolder,
                   std::string const &helpText,
                   T defaulValue ) :
          AbsArgument( placeHolder, helpText ),
          value_( defaulValue )
  {
    ArgumentManager::registerArgument( *this );
  }

  ~GenericArgument( )
  {
  }

  explicit GenericArgument( const GenericArgument& ) = delete;
  GenericArgument& operator=( const GenericArgument& ) = delete;

  constexpr std::string getType( ) const
  {
    return detail::type_traits<T>::type;
  }

  std::string getValue( ) const
  {
    return detail::to_string( value_ );
  }

  void setValue( std::string value )
  {
    value_ = detail::lexical_cast<T>( value );
  }

  operator T( ) const
  {
    return value_;
  }

  T value( ) const
  {
    return value_;
  }

  T operator*( ) const
  {
    return value_;
  }

private:
  T value_;
};

constexpr size_t placeHolderWidth = 25;
constexpr size_t typeValueWidth = 32;

struct DefaultHelpMessageCreator
{

  static std::string getHelpMessage( const DriverData& driverData )
  {
    std::string description;

    description += createUsageBlock( driverData );
    description += createPurposeBlock( driverData );
    description += createOptionalArgumentsBlock( driverData );
    description += createBuiltInArgumentsBlock( driverData );

    return description;
  }

private:
  static std::string createUsageBlock( const DriverData& driverData )
  {
    std::string description;

    description += "Usage: \n";

    description += driverData.driverName + " ";

    for ( auto& argument : driverData.requiredArguments )
    {
      description += argument.placeHolder + " ";
    }
    description += "[--options]\n";

    description += driverData.driverName + " --input inputFileName\n";

    return description;
  }

  static std::string createPurposeBlock( const DriverData& driverData )
  {
    std::string description;

    if ( not driverData.description.empty( ) )
    {
      description += "\nPurpose: \n\n" + driverData.description + "\n";
    }

    return description;
  }

  static std::string createOptionalArgumentsBlock( const DriverData& driverData )
  {
    auto arguments = driverData.optionalArguments;
    std::string argumentsType( "Optional arguments" );

    return createArgumentsBlock( arguments, argumentsType, "--" );
  }

  static std::string createBuiltInArgumentsBlock( const DriverData& driverData )
  {
    auto arguments = driverData.builtInArguments;
    std::string argumentsType( "Built-In arguments" );

    return createArgumentsBlock( arguments, argumentsType, "--" );
  }

  static std::string appendWhiteSpace( const std::string& input,
                                       size_t finalWidth )
  {
    std::string output = input;

    size_t currentWidth = output.size( );

    if ( currentWidth > finalWidth )
    {
      output += "\n\t" + std::string( finalWidth, ' ' );
    }
    else
    {
      size_t difference = finalWidth - currentWidth;

      output += std::string( difference, ' ' );
    }

    return output;
  }

  static std::string createArgumentsBlock( const std::vector<ArgumentData>& arguments,
                                           const std::string& argumentsType,
                                           const std::string& prefix )
  {
    std::string description;
    if ( arguments.empty( ) == false )
    {
      description += "\n" + argumentsType + ":\n";
      for ( auto& argument : arguments )
      {
        description += "\n\t";
        description += appendWhiteSpace( prefix + argument.placeHolder, placeHolderWidth );

        if ( !argument.type.empty( ) )
        {
          description += " : ";

          if ( argument.defaultValue.empty( ) )
          {
            description += appendWhiteSpace( argument.type, typeValueWidth );
          }
          else
          {
            description += appendWhiteSpace( argument.type + " (" + argument.defaultValue + ")", typeValueWidth );
          }
        }

        description += " : ";
        description += argument.helpText;
      }
      description += "\n";
    }

    return description;
  }
};

struct ExceptionPolicy
{
  static void error( std::string&& message );
};

struct CoutAndExitPolicy
{
  static void error( std::string&& message );
};

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

template<typename HelpMessagePolicy, typename ErrorPolicy, typename InputFilePolicy>
std::string GenericArgumentParser<HelpMessagePolicy, ErrorPolicy, InputFilePolicy>::description = "";

inline void ExceptionPolicy::error( std::string&& message )
{
  throw AutoArgsException( message );
}

inline void CoutAndExitPolicy::error( std::string&& message )
{
  std::cout << "Error: " << message + "\nTry '--help' for more information" << std::endl;
  exit( EXIT_FAILURE );
}

#define CHECK_FOR_ERROR( statement )          \
    try                                       \
    {                                         \
      statement;                              \
    }                                         \
    catch ( std::exception& e )               \
    {                                         \
      ErrorPolicy::error( e.what( ) );        \
    }

template<typename HelpMessagePolicy, typename ErrorPolicy, typename InputFilePolicy>
inline void GenericArgumentParser<HelpMessagePolicy, ErrorPolicy, InputFilePolicy>::parseCommandLine( int argc,
                                                                                                      char** argv )
{
  auto createStringVector = [](size_t lowerBound, size_t upperBound, char** argv)
  {
    StringVector argumentValues;

    for ( size_t i = lowerBound; i < upperBound; ++i )
    {
      argumentValues.push_back( argv[i] );
    } // end of i-loop

      return argumentValues;
    };

  std::string driverName = argv[0];
  size_t numberOfProvidedArguments = argc - 1;

  if ( numberOfProvidedArguments == 1 )
  {
    // Built in options
    {
      // - Provided -help -> print help message!
      if ( std::string( argv[1] ) == "--help" )
      {
        DriverData driverData = ArgumentManager::getDriverData( );
        driverData.driverName = driverName;
        driverData.description = description;
        driverData.builtInArguments.push_back( makeArgument( "help", "print this help message" ) );
        driverData.builtInArguments.push_back( makeArgument( "input", "Process an input file" ) );

        std::cout << HelpMessagePolicy::getHelpMessage( driverData ) << std::endl;
        exit( EXIT_SUCCESS );
      }

    }

    CHECK_FOR_ERROR( ArgumentManager::setArguments( { std::string( argv[1] ) } ) );
  }
  //- More than one argument given
  else
  {
    // Check if input file has been provided
    if ( ( numberOfProvidedArguments == 2 ) && ( std::string( argv[1] ) == "--input" ) )
    {
      PlaceHolderValueMap input = InputFilePolicy::parseInputFile( std::string( argv[2] ) );
      ArgumentManager::setArguments( input );

      return;
    }

    StringVector optionalArgumentValues = createStringVector( 1, numberOfProvidedArguments + 1, argv );

    CHECK_FOR_ERROR( ArgumentManager::setArguments( optionalArgumentValues ) );
  }

  // Create Input file
  CHECK_FOR_ERROR( createInputFile( driverName ) );
}

template<typename HelpMessagePolicy, typename ErrorPolicy, typename InputFilePolicy>
inline void GenericArgumentParser<HelpMessagePolicy, ErrorPolicy, InputFilePolicy>::setDriverDescription( const std::string& driverDescription )
{
  GenericArgumentParser<HelpMessagePolicy, ErrorPolicy, InputFilePolicy>::description = driverDescription;
}

template<typename HelpMessagePolicy, typename ErrorPolicy, typename InputFilePolicy>
inline void GenericArgumentParser<HelpMessagePolicy, ErrorPolicy, InputFilePolicy>::createInputFile( const std::string& driverName )
{
  std::string fileName = ".input.in";

  std::ofstream inputFile( fileName );

  if ( inputFile.is_open( ) )
  {
    inputFile << "# Input file for driver: " << driverName << "\n";
    inputFile << "# " << "\n";
    inputFile << listArguments( );
  }
}

template<typename HelpMessagePolicy, typename ErrorPolicy, typename InputFilePolicy>
void GenericArgumentParser<HelpMessagePolicy, ErrorPolicy, InputFilePolicy>::processArguments( const std::vector<ArgumentData>& arguments,
                                                                                               std::ostringstream& listOfArguments )
{
  for ( auto& argument : arguments )
  {
    listOfArguments << std::setw( 30 ) << std::right << argument.placeHolder << " : " << std::setw( 30 ) << std::left << argument.defaultValue << " # (" << argument.type << ") " << argument.helpText
        << "\n";
  }
}

using StringPair = std::pair<std::string,std::string>;

template<typename HelpMessagePolicy, typename ErrorPolicy, typename InputFilePolicy>
inline std::string GenericArgumentParser<HelpMessagePolicy, ErrorPolicy, InputFilePolicy>::listArguments( )
{
  DriverData data = ArgumentManager::getDriverData( );

  std::ostringstream listOfArguments;

  processArguments( data.requiredArguments, listOfArguments );
  processArguments( data.optionalArguments, listOfArguments );

  return listOfArguments.str( );
}

struct DefaultInputFileReader
{
  static PlaceHolderValueMap parseInputFile( const std::string& inputFile )
  {
    PlaceHolderValueMap result;

    // open input file
    std::ifstream infile;
    infile.open( inputFile.c_str( ) );

    detail::check( infile.is_open( ), "Couldn't open file: " + inputFile );

    size_t lineCounter = 0;

    // parse arguments
    for ( std::string line; std::getline( infile, line ); )
    {
      size_t pos = line.find( "#" );

      if ( pos != 0 ) // Is no comment line
      {
        removeInlineComment( line, pos );

        std::string placeHolder, value;
        std::tie( placeHolder, value ) = tokenizeLine( line, lineCounter );

        detail::check( not result.count( placeHolder ), "Placeholder in line " + std::to_string( lineCounter ) + " is not unique" );

        // Insert result
        result[placeHolder] = value;
      }

      lineCounter++;
    }

    return result;
  }

  static void removeInlineComment( std::string &line,
                                   size_t pos )
  {
    if ( pos != std::string::npos ) // Has a comment somewhere
    {
      line = line.substr( 0, pos );
    }
  }

  static StringPair tokenizeLine( std::string const &line,
                                  size_t counter )
  {
    auto pos = line.find( ":" );

    detail::check( pos, "No delimeter found on line " + std::to_string( counter ) );

    std::istringstream placeHolderStream( line.substr( 0, pos ) );
    std::istringstream valueStream( line.substr( pos + 1, line.size( ) ) );
    std::string placeHolder, value;

    // Strip leading and trailing whitespace
    placeHolderStream >> placeHolder;
    valueStream >> value;

    return std::make_pair( placeHolder, value );
  }
};

} // namespace autoargs
#endif // _AUTOARGS_HPP_ 
