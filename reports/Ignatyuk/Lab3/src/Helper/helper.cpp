#include "helper.hpp"

#include <QRandomGenerator>

#include <fstream>

std::int64_t Helper::f_get_random_number(const std::int64_t& c_From,
                                         const std::int64_t& c_To) {
  return c_From + QRandomGenerator::global()->generate() % (c_To - c_From + 1);
}

void Helper::f_read_line_from_file(const std::string& c_Filename,
                                   std::string& v_Data) {
  std::ifstream v_Fin(c_Filename);

  if (v_Fin.is_open()) {
    std::getline(v_Fin, v_Data);
    v_Fin.close();
  }
}

void Helper::f_write_to_file(const std::string& c_Filename,
                             const std::string& c_Data) {
  std::ofstream v_Fout(c_Filename);

  if (v_Fout.is_open()) {
    v_Fout << c_Data;
    v_Fout.close();
  }
}

extern "C" HELPER_EXPORT std::int64_t get_random_number(
    const std::int64_t& c_From, const std::int64_t& c_To) {
  return Helper::f_get_random_number(c_From, c_To);
}

extern "C" HELPER_EXPORT void read_line_from_file(const std::string& c_Filename,
                                                  std::string& v_Data) {
  Helper::f_read_line_from_file(c_Filename, v_Data);
}

extern "C" HELPER_EXPORT void write_to_file(const std::string& c_Filename,
                                            const std::string& c_Data) {
  Helper::f_write_to_file(c_Filename, c_Data);
}
