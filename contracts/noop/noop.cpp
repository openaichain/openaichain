/**
 *  @file
 *  @copyright defined in oac/LICENSE.txt
 */

#include <oaclib/oac.hpp>

namespace oac {

   class noop: public contract {
      public:
         noop( account_name self ): contract( self ) { }
         void anyaction( account_name from,
                         const std::string& /*type*/,
                         const std::string& /*data*/ )
         {
            require_auth( from );
         }
   };

   OACIO_ABI( noop, ( anyaction ) )

} /// oac     
