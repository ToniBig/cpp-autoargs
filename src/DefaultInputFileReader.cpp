/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

// --- Internal Includes ---
#include "../inc/DefaultInputFileReader.hpp"

// --- Standard Includes ---
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace adhocpp
{
namespace utilities
{

PlaceHolderValueMap DefaultInputFileReader::parseInputFile( const std::string& inputFile )
{
  PlaceHolderValueMap result;

  // open input file
  std::ifstream infile;
  infile.open( inputFile.c_str( ) );

  if ( infile.is_open( ) == false )
  {
    throw std::runtime_error( "Couldn't open file: " + inputFile );
  }

  size_t counter = 0;

  // parse arguments
  for ( std::string line; getline( infile, line ); )
  {

    // Remove comment
    size_t found = line.find( "#" );

    if ( found == 0 )
    {
      // Comment line!
    }
    else
    {
      std::string uncommentedLine( line );

      if ( found != std::string::npos )
      {
        uncommentedLine = line.substr( 0, found );
      }

      // Tokenize cleaned line
      found = uncommentedLine.find( ":" );

      if ( !found )
      {
        throw std::runtime_error( "No delimeter found on line " + std::to_string( counter ) );
      }

      std::istringstream placeHolderStream( uncommentedLine.substr( 0, found ) );
      std::istringstream valueStream( uncommentedLine.substr( found + 1, uncommentedLine.size( ) ) );
      std::string placeHolder;
      std::string value;

      // Strip leading and trailing whitespaces
      placeHolderStream >> placeHolder;
      valueStream >> value;

      if ( result.count( placeHolder ) )
      {
        throw std::runtime_error( "Placeholder in line " + std::to_string( counter ) + " is not unique" );
      }

      // Insert result
      result[placeHolder] = value;
    }

    counter++;
  }

  return result;
}

} // namespace utilities 
} // namespace adhocpp
