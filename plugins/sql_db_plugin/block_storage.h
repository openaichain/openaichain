/**
 *  @file
 *  @copyright defined in oac/LICENSE.txt
 */

#pragma once

#include "consumer_core.h"

#include <oac/chain/block_state.hpp>

namespace oac {

class block_storage : public consumer_core<chain::block_state_ptr>
{
public:
    void consume(const std::vector<chain::block_state_ptr>& blocks) override;
};

} // namespace
