/**
 *  @file
 *  @copyright defined in oac/LICENSE.txt
 */
#pragma once
#include <fc/exception/exception.hpp>

namespace oac { namespace client { namespace help {
   bool print_recognized_errors(const fc::exception& e, const bool verbose_errors);
   bool print_help_text(const fc::exception& e);
}}}