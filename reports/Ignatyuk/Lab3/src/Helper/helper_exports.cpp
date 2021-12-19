extern "C" HELPER_EXPORT std::int64_t _get_random_number(
    const std::int64_t& c_from, const std::int64_t& c_to) {
  return Helper::f_get_random_number(c_From, c_To);
}

extern "C" HELPER_EXPORT void _write_to_file(const std::string& c_Filename,
                                             const std::string& c_Data) {
  Helper::_write_to_file(c_Filename, c_Data);
}
