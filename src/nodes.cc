#include "nodes.hh"

#include <iostream>

/* Node */

void
Node::accept(const Visitor& visitor) const {
  std::cout << "Visitor visits a node" << std::endl;
  visitor.visit(*this);
}

/* Exps */

void
Exps::add_exp(exp_ptr_t exp) {
  exps_.push_back(exp);
}

const Exps::exp_vec_t& 
Exps::get_exps() const {
  return exps_;
}

void
Exps::accept(const Visitor& visitor) const {
  visitor.visit(*this);
}

/* Value */

Value::Value(std::string name)
  : name_(name), value_(0), type_(VARIABLE)
{}

Value::Value(int value)
  : name_(""), value_(value), type_(STATIC)
{}

const std::string&
Value::get_name() const {
  return name_;
}

const int&
Value::get_value() const {
  return value_;
}

const Value::value_t&
Value::get_type() const {
  return type_;
}

void
Value::accept(const Visitor& visitor) const {
  visitor.visit(*this);
}

/* PrintExp */

PrintExp::PrintExp(val_ptr_t value)
  : value_(value)
{}

const PrintExp::val_ptr_t&
PrintExp::get_value() const {
  return value_;
}

void
PrintExp::accept(const Visitor& visitor) const {
  visitor.visit(*this);
}

/* AssignExp */

AssignExp::AssignExp(val_ptr_t lhs, val_ptr_t rhs)
  : lhs_(lhs), rhs_(rhs)
{}

const AssignExp::val_ptr_t&
AssignExp::get_lhs() const {
  return lhs_;
}

const AssignExp::val_ptr_t&
AssignExp::get_rhs() const {
  return rhs_;
}

void
AssignExp::accept(const Visitor& visitor) const {
  visitor.visit(*this);
}

/* FunctionDec */

FunctionDec::FunctionDec(std::string name, exps_ptr_t exps)
  : name_(name), exps_(exps)
{}

const std::string&
FunctionDec::get_name() const {
  return name_;
}

const FunctionDec::exps_ptr_t&
FunctionDec::get_exps() const {
  return exps_;
}

void
FunctionDec::accept(const Visitor& visitor) const {
  visitor.visit(*this);
}

/* FunctionCall */

FunctionCall::FunctionCall(std::string name)
  : name_(name)
{}

const std::string&
FunctionCall::get_name() const {
  return name_;
}

const FunctionCall::fdec_ptr_t
FunctionCall::get_def() const {
  return def_;
}

void
FunctionCall::accept(const Visitor& visitor) const {
  visitor.visit(*this);
}
