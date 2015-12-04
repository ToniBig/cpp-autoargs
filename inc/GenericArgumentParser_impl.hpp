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
#include "../inc/ArgumentManager.hpp"

// --- Standard Includes ---
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace autoargs
{

template<typename HelpMessagePolicy, typename ErrorPolicy, typename InputFilePolicy>
std::string GenericArgumentParser<HelpMessagePolicy, ErrorPolicy, InputFilePolicy>::description = "";

inline void ExceptionPolicy::error( std::string message )
{
  throw std::runtime_error( message );
}

inline void CoutAndExitPolicy::error( std::string message )
{
  std::cout << "Error: " << message + "\nTry '--help' for more information" << std::endl;
  exit (EXIT_FAILURE);
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
        DriverData driverData = ArgumentManager::getInstance( ).getDriverData( );
        driverData.driverName = driverName;
        driverData.description = description;
        driverData.builtInArguments.push_back( makeArgument( "help", "print this help message" ) );
        driverData.builtInArguments.push_back( makeArgument( "input", "Process an input file" ) );

        std::cout << HelpMessagePolicy::getHelpMessage( driverData ) << std::endl;
        exit( EXIT_SUCCESS );
      }

    }

    CHECK_FOR_ERROR( ArgumentManager::getInstance( ).setArguments( { std::string( argv[1] ) } ) );
  }
  //- More than one argument given
  else
  {
    // Check if input file has been provided
    if ( ( numberOfProvidedArguments == 2 ) && ( std::string( argv[1] ) == "--input" ) )
    {
      PlaceHolderValueMap input = InputFilePolicy::parseInputFile( std::string( argv[2] ) );
      ArgumentManager::getInstance( ).setArguments( input );

      return;
    }

    StringVector optionalArgumentValues = createStringVector( 1, numberOfProvidedArguments + 1, argv );

    CHECK_FOR_ERROR( ArgumentManager::getInstance( ).setArguments( optionalArgumentValues ) );
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
    inputFile.close( );
  }
}

template<typename HelpMessagePolicy, typename ErrorPolicy, typename InputFilePolicy>
void GenericArgumentParser<HelpMessagePolicy, ErrorPolicy, InputFilePolicy>::processArguments( const std::vector<ArgumentData>& arguments,
                                                                                               std::ostringstream& listOfArguments )
{
  for ( auto& argument : arguments )
  {
    listOfArguments << std::setw( 30 ) << std::right << argument.placeHolder << " : " << std::setw( 30 ) << std::left << argument.defaultValue << " # (" << argument.type << ") " << argument.helpText << "\n";
  }
}

template<typename HelpMessagePolicy, typename ErrorPolicy, typename InputFilePolicy>
inline std::string GenericArgumentParser<HelpMessagePolicy, ErrorPolicy, InputFilePolicy>::listArguments( )
{
  DriverData data = ArgumentManager::getInstance( ).getDriverData( );

  std::ostringstream listOfArguments;

  processArguments( data.requiredArguments, listOfArguments );
  processArguments( data.optionalArguments, listOfArguments );

  return listOfArguments.str( );
}

} // namespace autoargs

