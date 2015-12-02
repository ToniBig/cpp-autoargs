/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 *   AdhoC++, 2012 Chair for Computation in Engineering, All Rights Reserved.  */

#ifndef UTILITIES_DEFAULTINPUTFILEREADER_HPP_
#define UTILITIES_DEFAULTINPUTFILEREADER_HPP_

// --- Standard Includes ---
#include <map>
#include <string>

namespace adhocpp {
namespace utilities {

typedef std::map<std::string, std::string> PlaceHolderValueMap;

class DefaultInputFileReader
{
public:

  static PlaceHolderValueMap parseInputFile( const std::string& inputFile );

private:
  explicit DefaultInputFileReader( const DefaultInputFileReader& );
  DefaultInputFileReader& operator=( const DefaultInputFileReader& );

};

} // namespace utilities 
} // namespace adhocpp
#endif // UTILITIES_DEFAULTINPUTFILEREADER_HPP_
