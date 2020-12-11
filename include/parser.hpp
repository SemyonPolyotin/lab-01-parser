// Copyright 2020 Семён Полётин

#ifndef INCLUDE_PARSER_HPP_
#define INCLUDE_PARSER_HPP_

#include <string>
#include <vector>

#include "student.hpp"
using nlohmann::json;

class Parser {
 public:
  explicit Parser(const std::string& jsonPath);
  void printColumns(std::ostream& out) const;
  void print_lines(std::ostream& out) const;
  friend std::ostream& operator<<(std::ostream& out, const Parser& pars);

 private:
  std::vector<Student> _students;
  std::vector<size_t> _columnWidth{0, 9, 7, 15};
};

#endif  // INCLUDE_PARSER_HPP_
