#include <stdexcept>
#include <iostream>

#include "visitor.hh"

/* Visitor (does nothing) */

void
Visitor::visit(const Node& node) const {
  (void) node;
  throw std::invalid_argument("Node instance must have final dynamic type");
}

void
Visitor::visit(const Exps& exps) const {
  for(auto it = exps.get_exps().begin(); it != exps.get_exps().end(); it++) {
    (*it)->accept(*this);
  } 
}

void
Visitor::visit(const Exp& exp) const {
  (void) exp;
  throw std::invalid_argument("Exp instance must have final dynamic type");
}

void
Visitor::visit(const Value& value) const {
  (void) value;
}

void
Visitor::visit(const PrintExp& printExp) const {
  printExp.get_value()->accept(*this);
}

void
Visitor::visit(const AssignExp& assignExp) const {
  assignExp.get_lhs()->accept(*this);
  assignExp.get_rhs()->accept(*this);
}

void
Visitor::visit(const FunctionDec& functionDec) const {
  functionDec.get_exps()->accept(*this);
}

void
Visitor::visit(const FunctionCall& functionCall) const {
  (void) functionCall;
}

/* Printer */

void
Printer::visit(const Exps& exps) const {
  for(auto it = exps.get_exps().begin(); it != exps.get_exps().end(); it++) {
    (*it)->accept(*this);
    if (std::next(it) != exps.get_exps().end())
      std::cout << " ";
  } 
}

void
Printer::visit(const Value& value) const {
  switch (value.get_type()) {
    case Value::VARIABLE:
      std::cout << value.get_name();
      break;
    case Value::STATIC:
      std::cout << value.get_value();
      break;
  }
}

void
Printer::visit(const PrintExp& printExp) const {
  std::cout << "print ";
  printExp.get_value()->accept(*this); 
}

void
Printer::visit(const AssignExp& assignExp) const {
  assignExp.get_lhs()->accept(*this);
  std::cout << " = ";
  assignExp.get_rhs()->accept(*this);
}

void
Printer::visit(const FunctionDec& functionDec) const {
  std::cout << "function ";
  std::cout << functionDec.get_name();
  std::cout << " { ";
  functionDec.get_exps()->accept(*this);
  std::cout << " }";
}

void
Printer::visit(const FunctionCall& functionCall) const {
  std::cout << functionCall.get_name();
  std::cout << " ( )";
}
