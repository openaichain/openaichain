/**
 *  @file
 *  @copyright defined in oac/LICENSE.txt
 */

#include <oac/utilities/tempdir.hpp>

#include <cstdlib>

namespace oac { namespace utilities {

fc::path temp_directory_path()
{
   const char* oac_tempdir = getenv("OAC_TEMPDIR");
   if( oac_tempdir != nullptr )
      return fc::path( oac_tempdir );
   return fc::temp_directory_path() / "oac-tmp";
}

} } // oac::utilities
