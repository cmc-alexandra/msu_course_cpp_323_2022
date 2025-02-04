#pragma once
#include <fstream>
#include <string>

namespace uni_course_cpp {
class Logger {
 public:
  void log(const std::string& string);
  static Logger& get_logger();
  std::string get_current_date_time();
  Logger(const Logger&) = delete;
  void operator=(const Logger&) = delete;
  Logger(Logger&& other) = delete;
  void operator=(Logger&& other) = delete;

 private:
  std::ofstream log_stream_;
  Logger();
  ~Logger() { log_stream_.close(); };
};
}  // namespace uni_course_cpp
