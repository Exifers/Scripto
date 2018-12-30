#include <iostream>
#include <stdexcept>

#include "interpreter.hh"

void Interpreter::resolve_value(std::shared_ptr<Value> value) {
  if (value->get_memory() == Value::LVALUE) {
    if (int_values_.find(value->get_name()) != int_values_.end()) {
      value->get_int_value() = int_values_[value->get_name()];
      value->get_type() = Value::INT;
      return;
    } else if (string_values_.find(value->get_name()) != string_values_.end()) {
      value->get_string_value() = string_values_[value->get_name()];
      value->get_type() = Value::STRING;
      return;
    } else {
      throw std::invalid_argument("Unknown variable: " + value->get_name());
    }
  }
}

void Interpreter::set_int_value(std::string &name, int value) {
  int_values_[name] = value;
  if (string_values_.find(name) != string_values_.end()) {
    string_values_.erase(string_values_.find(name));
  }
}

void Interpreter::set_string_value(std::string &name, std::string &value) {
  string_values_[name] = value;
  if (int_values_.find(name) != int_values_.end()) {
    int_values_.erase(int_values_.find(name));
  }
}

void Interpreter::set_function(std::string &name,
                               std::shared_ptr<Node> function) {
  functions_[name] = function;
}

std::shared_ptr<Node> Interpreter::read_function(FunctionCall &functionCall) {
  if (functions_.find(functionCall.get_name()) == functions_.end()) {
    throw std::invalid_argument("Unknown function: " + functionCall.get_name());
  }
  return functions_[functionCall.get_name()];
}

void Interpreter::visit(PrintExp &printExp) {
  resolve_value(printExp.get_value());
  switch (printExp.get_value()->get_type()) {
  case Value::INT:
    std::cout << printExp.get_value()->get_int_value() << std::endl;
    break;
  case Value::STRING:
    std::cout << printExp.get_value()->get_string_value() << std::endl;
    break;
  }
}

void Interpreter::visit(AssignExp &assignExp) {
  resolve_value((assignExp.get_rhs()));
  switch (assignExp.get_rhs()->get_type()) {
  case Value::INT:
    set_int_value(assignExp.get_lhs()->get_name(),
                  assignExp.get_rhs()->get_int_value());
    break;
  case Value::STRING:
    set_string_value(assignExp.get_lhs()->get_name(),
                     assignExp.get_rhs()->get_string_value());
    break;
  }
}

void Interpreter::visit(FunctionDec &functionDec) {
  set_function(functionDec.get_name(), functionDec.get_exps());
}

void Interpreter::visit(FunctionCall &functionCall) {
  auto function = read_function(functionCall);
  function->accept(*this);
}

void Interpreter::visit(IfStmt &ifStmt) {
  resolve_value(ifStmt.get_lhs());
  resolve_value(ifStmt.get_rhs());

  if (ifStmt.get_lhs()->get_type() != ifStmt.get_rhs()->get_type()) {
    throw std::invalid_argument("Cannot compare values of type " +
                                std::to_string(ifStmt.get_lhs()->get_type()) +
                                " and " +
                                std::to_string(ifStmt.get_rhs()->get_type()));
  }

  switch (ifStmt.get_lhs()->get_type()) {
  case Value::INT:
    if (ifStmt.get_lhs()->get_int_value() ==
        ifStmt.get_rhs()->get_int_value()) {
      ifStmt.get_exps()->accept(*this);
    } else if (ifStmt.getElse_exps() != nullptr) {
      ifStmt.getElse_exps()->accept(*this);
    }
    break;
  case Value::STRING:
    if (ifStmt.get_lhs()->get_string_value() ==
        ifStmt.get_rhs()->get_string_value()) {
      ifStmt.get_exps()->accept(*this);
    } else if (ifStmt.getElse_exps() != nullptr) {
      ifStmt.getElse_exps()->accept(*this);
    }
    break;
  }
}

void Interpreter::visit(RepeatStmt &repeatStmt) {
  std::string e("e");
  for (int i = 0; i < repeatStmt.get_num()->get_int_value(); i++) {
    set_int_value(e, i);
    repeatStmt.get_exps()->accept(*this);
  }
}
