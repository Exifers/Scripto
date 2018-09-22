#include "nodes.hh"

#include <iostream>

/* Node */

void
Node::accept(Visitor& visitor) {
  visitor.visit(*this);
}

/* Exps */

void
Exps::add_exp(exp_ptr_t exp) {
  exps_.push_back(exp);
}

Exps::exp_vec_t& 
Exps::get_exps() {
  return exps_;
}

void
Exps::accept(Visitor& visitor) {
  visitor.visit(*this);
}

/* Value */

Value::Value(const std::string& name)
  : name_(name), value_(0), type_(VARIABLE)
{}

Value::Value(int value)
  : name_(""), value_(value), type_(STATIC)
{}

Value::Value(const std::string& name, int value, value_t type,
             const std::string& text_value)
  : name_(name), value_(value), type_(type), text_value_(text_value)
{}

std::shared_ptr<Value>
Value::make_text_value(const std::string& value) {
  return std::make_shared<Value>("", 0, TEXT, value);
}

std::string&
Value::get_name() {
  return name_;
}

int&
Value::get_value() {
  return value_;
}

std::string&
Value::get_text_value() {
  return text_value_;
}

Value::value_t&
Value::get_type() {
  return type_;
}

void
Value::accept(Visitor& visitor) {
  visitor.visit(*this);
}

/* PrintExp */

PrintExp::PrintExp(val_ptr_t value)
  : value_(value)
{}

PrintExp::val_ptr_t&
PrintExp::get_value() {
  return value_;
}

void
PrintExp::accept(Visitor& visitor) {
  visitor.visit(*this);
}

/* AssignExp */

AssignExp::AssignExp(val_ptr_t lhs, val_ptr_t rhs)
  : lhs_(lhs), rhs_(rhs)
{}

AssignExp::val_ptr_t&
AssignExp::get_lhs() {
  return lhs_;
}

AssignExp::val_ptr_t&
AssignExp::get_rhs() {
  return rhs_;
}

void
AssignExp::accept(Visitor& visitor) {
  visitor.visit(*this);
}

/* FunctionDec */

FunctionDec::FunctionDec(std::string name, exps_ptr_t exps)
  : name_(name), exps_(exps)
{}

std::string&
FunctionDec::get_name() {
  return name_;
}

FunctionDec::exps_ptr_t&
FunctionDec::get_exps() {
  return exps_;
}

void
FunctionDec::accept(Visitor& visitor) {
  visitor.visit(*this);
}

/* FunctionCall */

FunctionCall::FunctionCall(std::string name)
  : name_(name)
{}

std::string&
FunctionCall::get_name() {
  return name_;
}

FunctionCall::fdec_ptr_t
FunctionCall::get_def() {
  return def_;
}

void
FunctionCall::accept(Visitor& visitor) {
  visitor.visit(*this);
}

/* IfStmt */

IfStmt::IfStmt(value_ptr_t lhs, value_ptr_t rhs, exps_ptr_t exps)
  : lhs_(lhs), rhs_(rhs), exps_(exps)
{}

IfStmt::value_ptr_t
IfStmt::get_lhs() {
  return lhs_;
}

IfStmt::value_ptr_t
IfStmt::get_rhs() {
  return rhs_;
}

IfStmt::exps_ptr_t
IfStmt::get_exps() {
  return exps_;
}

void
IfStmt::accept(Visitor& visitor) {
  visitor.visit(*this);
}
