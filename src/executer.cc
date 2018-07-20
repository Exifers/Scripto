#include <stdexcept>
#include <iostream>

#include "executer.hh"

int
Executer::read_value(Value& value) {
  if (value.get_type() == Value::STATIC) {
    return value.get_value();
  }
  if (values_.find(value.get_name()) == values_.end()) {
    throw std::invalid_argument("Unknown variable: " + value.get_name());
  } 
  return values_[value.get_name()];
}


void
Executer::set_value(std::string& name, int value) {
  values_[name] = value;
}

std::shared_ptr<Node>
Executer::read_function(FunctionCall& functionCall) {
  if (functions_.find(functionCall.get_name()) == functions_.end()) {
    throw std::invalid_argument("Unknown function: " + functionCall.get_name());
  }
  return functions_[functionCall.get_name()];
}

void
Executer::set_function(std::string& name,
  std::shared_ptr<Node> function) {
  functions_[name] = function;
}

void
Executer::visit(PrintExp& printExp) {
  std::cout << read_value(*printExp.get_value()) << std::endl;
}

void
Executer::visit(AssignExp& assignExp) {
  set_value(assignExp.get_lhs()->get_name(), read_value(*assignExp.get_rhs()));
}

void
Executer::visit(FunctionDec& functionDec) {
  set_function(functionDec.get_name(), functionDec.get_exps());
}

void
Executer::visit(FunctionCall& functionCall) {
  auto function = read_function(functionCall);
  function->accept(*this);
}

void
Executer::visit(IfStmt& ifStmt) {
  if (read_value(*ifStmt.get_lhs()) == read_value(*ifStmt.get_rhs())) {
    ifStmt.get_exps()->accept(*this);
  }
}
