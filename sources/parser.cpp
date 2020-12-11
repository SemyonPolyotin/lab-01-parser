// Copyright 2020 Семён Полётин

#include "parser.hpp"

Parser::Parser(const std::string& jsonPath) {
  json data;
  if (jsonPath[0] != '{') {
    if (jsonPath.empty()) {
      throw std::invalid_argument("JsonPath is empty!");
    }
    std::ifstream file(jsonPath);
    if (!file) {
      throw std::runtime_error("Unable to open json: " + jsonPath);
    }
    file >> data;
  } else {
    data = json::parse(jsonPath);
  }
  if (data.empty()) {
    throw std::invalid_argument("No data in json!");
  }
  if (!data.at("items").is_array()) {
    throw std::invalid_argument("json is not array!");
  }
  if (data.at("items").size() != data.at("_meta").at("count")) {
    throw std::out_of_range("_meta.count != len(items)");
  }
  for (auto const& student : data.at("items")) {
    _students.push_back(Student(student));
  }
  for (auto const& student : _students) {
    if (student.getName().size() + 3 > _columnWidth[0]) {
      _columnWidth[0] = student.getName().size() + 3;
    }
  }
}

void Parser::printColumns(std::ostream& out) const {
  out << std::setfill(' ') << std::left << std::setw(_columnWidth[0])
      << "| name" << std::setw(_columnWidth[1]) << "| group"
      << std::setw(_columnWidth[2]) << "| avg" << std::setw(_columnWidth[3])
      << "| debt" << '|' << std::endl;
}

void Parser::print_lines(std::ostream& out) const {
  for (size_t i = 0; i < 4; ++i) {
    out << std::setfill('-') << std::setw(_columnWidth[i]) << "|";
  }
  out << '|' << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Parser& pars) {
  pars.printColumns(out);
  pars.print_lines(out);
  for (size_t i = 0; i < pars._students.size(); ++i) {
    out << std::setfill(' ') << std::setw(pars._columnWidth[0])
        << "| " + pars._students[i].getName();
    if (pars._students[i].getGroup().type() == typeid(std::string)) {
      out << std::setw(pars._columnWidth[1])
          << "| " + std::any_cast<std::string>(pars._students[i].getGroup());
    } else {
      out << "| " << std::setw(pars._columnWidth[1] - 2)
          << std::any_cast<size_t>(pars._students[i].getGroup());
    }
    if (pars._students[i].getAvg().type() == typeid(std::nullptr_t)) {
      out << "| " << std::setw(pars._columnWidth[2] - 2) << "null";
    } else if (pars._students[i].getAvg().type() == typeid(std::string)) {
      out << std::setw(pars._columnWidth[2])
          << "| " + std::any_cast<std::string>(pars._students[i].getAvg());
    } else if (pars._students[i].getAvg().type() == typeid(std::size_t)) {
      out << "| " << std::setw(pars._columnWidth[2] - 2)
          << std::any_cast<size_t>(pars._students[i].getAvg());
    } else {
      out << "| " << std::setw(pars._columnWidth[2] - 2)
          << std::any_cast<double>(pars._students[i].getAvg());
    }
    if (pars._students[i].getDebt().type() == typeid(std::nullptr_t)) {
      out << "| " << std::setw(pars._columnWidth[3] - 2) << "null";
    } else if (pars._students[i].getDebt().type() == typeid(std::string)) {
      out << std::setw(pars._columnWidth[3])
          << "| " + std::any_cast<std::string>(pars._students[i].getDebt());
    } else {
      out << "| "
          << std::any_cast<std::vector<std::string>>(
                 pars._students[i].getDebt())
                 .size()
          << std::setw(pars._columnWidth[3] - 3) << " items";
    }
    out << '|' << std::endl;
    pars.print_lines(out);
  }
  return out;
}
