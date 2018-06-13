/**
 *  @file
 *  @copyright defined in oac/LICENSE.txt
 */
#pragma once

#include <oac/chain/types.hpp>
#include <oac/chain/contract_types.hpp>

namespace oac { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_oac_newaccount(apply_context&);
   void apply_oac_updateauth(apply_context&);
   void apply_oac_deleteauth(apply_context&);
   void apply_oac_linkauth(apply_context&);
   void apply_oac_unlinkauth(apply_context&);

   /*
   void apply_oac_postrecovery(apply_context&);
   void apply_oac_passrecovery(apply_context&);
   void apply_oac_vetorecovery(apply_context&);
   */

   void apply_oac_setcode(apply_context&);
   void apply_oac_setabi(apply_context&);

   void apply_oac_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace oac::chain
