#include <oaclib/oac.hpp>
#include <oaclib/print.hpp>
using namespace oac;

class payloadless : public oac::contract {
  public:
      using contract::contract;

      void doit() {
         print( "Im a payloadless action" );
      }
};

OACIO_ABI( payloadless, (doit) )
