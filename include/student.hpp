// Copyright 2020 Семён Полётин

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#endif  //INCLUDE_STUDENT_HPP_

#include "../../../../.hunter/_Base/9a3594a/a04cd14/c351cc1/Install/include/nlohmann/json.hpp"
#include "any"
#include "exception"
#include "fstream"
#include "iomanip"
#include "string"

using nlohmann::json;

class Student {
 public:
  explicit Student(const json& j);
  const std::string& getName() const;
  const std::any& getGroup() const;
  const std::any& getAvg() const;
  const std::any& getDebt() const;
  void printName(std::ostream egg) const;
  void printGroup(std::ostream egg) const;
  void printAvg(std::ostream egg) const;
  void printDebt(std::ostream egg) const;

 private:
  std::string _name;
  std::any _group;
  std::any _avg;
  std::any _debt;
};
