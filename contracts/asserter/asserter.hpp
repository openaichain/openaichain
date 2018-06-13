/**
 *  @file
 *  @copyright defined in oac/LICENSE.txt
 */

#include <oaclib/oac.hpp>

namespace asserter {
   struct assertdef {
      int8_t      condition;
      std::string message;

      OACLIB_SERIALIZE( assertdef, (condition)(message) )
   };
}
