#include "student.hpp"

using nlohmann::json;

Student::Student(const json& js) {
  if (js.empty()) {
    throw std::invalid_argument("Json has no data!");
  }

  if (js.at("name").is_string()) {
    _name = js.at("name").get<std::string>();
  } else {
    throw std::invalid_argument("Name type does not match");
  }

  if (js.at("group").is_string()) {
    _group = js.at("group").get<std::string>();
  } else if (js.at("group").is_number_unsigned()) {
    _group = js.at("group").get<size_t>();
  } else {
    throw std::invalid_argument("Group type does not match");
  }

  if (js.at("avg").is_null()) {
    _avg = nullptr;
  } else if (js.at("avg").is_string()) {
    _avg = js.at("avg").get<std::string>();
  } else if (js.at("avg").is_number_float()) {
    _avg = js.at("avg").get<double>();
  } else if (js.at("avg").is_number_unsigned()) {
    _avg = js.at("avg").get<size_t>();
  } else {
    throw std::invalid_argument("Avg type does not match");
  }

  if (js.at("debt").is_null()) {
    _debt = nullptr;
  } else if (js.at("debt").is_string()) {
    _debt = js.at("debt").get<std::string>();
  } else if (js.at("debt").is_array()) {
    _debt = js.at("debt").get<std::vector<std::string>>();
  } else {
    throw std::invalid_argument("Debt is not correct");
  }
}

const std::string& Student::getName() const { return _name; }
const std::any& Student::getGroup() const { return _group; }
const std::any& Student::getAvg() const { return _avg; }
const std::any& Student::getDebt() const { return _debt; }