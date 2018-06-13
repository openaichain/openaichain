/**
 *  @file
 *  @copyright defined in oac/LICENSE.txt
 */
#pragma once

#include <oaclib/oac.hpp>
#include <oaclib/token.hpp>
#include <oaclib/reflect.hpp>
#include <oaclib/generic_currency.hpp>

#include <bancor/converter.hpp>
#include <currency/currency.hpp>

namespace bancor {
   typedef oac::generic_currency< oac::token<N(other),S(4,OTHER)> >  other_currency;
   typedef oac::generic_currency< oac::token<N(bancor),S(4,RELAY)> > relay_currency;
   typedef oac::generic_currency< oac::token<N(currency),S(4,CUR)> > cur_currency;

   typedef converter<relay_currency, other_currency, cur_currency > example_converter;
} /// bancor

