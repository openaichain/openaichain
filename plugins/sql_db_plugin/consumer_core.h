/**
 *  @file
 *  @copyright defined in oac/LICENSE.txt
 */

#pragma once

#include <vector>

namespace oac {

template<typename T>
class consumer_core {
public:
    virtual ~consumer_core() {}
    virtual void consume(const std::vector<T>& elements) = 0;
};

} // namespace


