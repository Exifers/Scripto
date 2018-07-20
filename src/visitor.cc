#include <stdexcept>
#include <iostream>

#include "visitor.hh"

/* Visitor (does nothing) */

void
Visitor::visit(Node& node) {
  (void) node;
  throw std::invalid_argument("Node instance must have final dynamic type");
}

void
Visitor::visit(Exps& exps) {
  for(auto it = exps.get_exps().begin(); it != exps.get_exps().end(); it++) {
    (*it)->accept(*this);
  } 
}

void
Visitor::visit(Exp& exp) {
  (void) exp;
  throw std::invalid_argument("Exp instance must have final dynamic type");
}

void
Visitor::visit(Value& value) {
  (void) value;
}

void
Visitor::visit(PrintExp& printExp) {
  printExp.get_value()->accept(*this);
}

void
Visitor::visit(AssignExp& assignExp) {
  assignExp.get_lhs()->accept(*this);
  assignExp.get_rhs()->accept(*this);
}

void
Visitor::visit(FunctionDec& functionDec) {
  functionDec.get_exps()->accept(*this);
}

void
Visitor::visit(FunctionCall& functionCall) {
  (void) functionCall;
}

void
Visitor::visit(IfStmt& ifStmt) {
  ifStmt.get_lhs()->accept(*this);
  ifStmt.get_rhs()->accept(*this);
  ifStmt.get_exps()->accept(*this);
}

/* Printer */

void
Printer::visit(Exps& exps) {
  for(auto it = exps.get_exps().begin(); it != exps.get_exps().end(); it++) {
    (*it)->accept(*this);
    if (std::next(it) != exps.get_exps().end())
      std::cout << " ";
  } 
}

void
Printer::visit(Value& value) {
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
Printer::visit(PrintExp& printExp) {
  std::cout << "print ";
  printExp.get_value()->accept(*this); 
}

void
Printer::visit(AssignExp& assignExp) {
  assignExp.get_lhs()->accept(*this);
  std::cout << " = ";
  assignExp.get_rhs()->accept(*this);
}

void
Printer::visit(FunctionDec& functionDec) {
  std::cout << "function ";
  std::cout << functionDec.get_name();
  std::cout << " { ";
  functionDec.get_exps()->accept(*this);
  std::cout << " }";
}

void
Printer::visit(FunctionCall& functionCall) {
  std::cout << functionCall.get_name();
  std::cout << " ( )";
}

void
Printer::visit(IfStmt& ifStmt) {
  std::cout << "if ( ";
  ifStmt.get_lhs()->accept(*this);
  std::cout << " == ";
  ifStmt.get_rhs()->accept(*this);
  std::cout << " ) { ";
  ifStmt.get_exps()->accept(*this);
  std::cout << " }";
}
