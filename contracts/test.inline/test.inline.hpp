#include <oaclib/oac.hpp>
#include <oaclib/privileged.h>
#include <oaclib/producer_schedule.hpp>

namespace oac {

   class testinline : public contract {
      public:
         testinline( action_name self ):contract(self){}

         void reqauth( account_name from ) {
            require_auth( from );
         }

         void forward( action_name reqauth, account_name forward_code, account_name forward_auth ) {
            require_auth( reqauth );
            INLINE_ACTION_SENDER(testinline, reqauth)( forward_code, {forward_auth,N(active)}, {forward_auth} );
            //SEND_INLINE_ACTION( testinline(forward_code), reqauth, {forward_auth,N(active)}, {forward_auth} );
            //oac::dispatch_inline<account_name>( N(forward_code), N(reqauth), {{forward_auth, N(active)}}, {forward_auth} );
         }
   };

} /// namespace oac
