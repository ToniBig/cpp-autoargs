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
#include "../inc/DefaultInputFileReader.hpp"

// --- Standard Includes ---
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace autoargs
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

} // namespace autoargs
