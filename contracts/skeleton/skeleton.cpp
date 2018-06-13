#include <oaclib/oac.hpp>

using namespace oac;

class hello : public oac::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
      }
};

OACIO_ABI( hello, (hi) )
