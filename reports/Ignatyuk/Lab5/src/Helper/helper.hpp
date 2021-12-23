#pragma once

#ifndef HELPER_HPP
#define HELPER_HPP

#include "Helper_global.hpp"

class HELPER_EXPORT Helper {
 public:
  static std::int64_t f_get_random_number(const std::int64_t& c_From,
                                          const std::int64_t& c_To);

  static void f_read_line_from_file(const std::string& c_Filename,
                                    std::string& v_Data);

  static void f_write_to_file(const std::string& c_Filename,
                              const std::string& c_Data);
};

#endif  // HELPER_HPP
