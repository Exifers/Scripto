#include "nodes.hh"

#include <iostream>

/* Node */

void Node::accept(Visitor &visitor) { visitor.visit(*this); }

/* Exps */

void Exps::add_exp(exp_ptr_t exp) { exps_.push_back(exp); }

Exps::exp_vec_t &Exps::get_exps() { return exps_; }

void Exps::accept(Visitor &visitor) { visitor.visit(*this); }

/* Value */

Value::Value(std::string value)
    : name_(""), int_value_(0), string_value_(value), memory_(RVALUE),
      type_(STRING) {}

Value::Value(int value)
    : name_(""), int_value_(value), string_value_(""), memory_(RVALUE),
      type_(INT) {}

Value::Value(std::string name, std::string value)
    : name_(name), int_value_(0), string_value_(value), memory_(LVALUE) {}

Value::Value(std::string name, int value)
    : name_(name), int_value_(value), string_value_(""), memory_(LVALUE) {}

std::string &Value::get_name() { return name_; }

int &Value::get_int_value() { return int_value_; }

Value::memory_t &Value::get_memory() { return memory_; }

Value::type_t &Value::get_type() { return type_; }

std::string &Value::get_string_value() { return string_value_; }

void Value::accept(Visitor &visitor) { visitor.visit(*this); }

/* PrintExp */

PrintExp::PrintExp(val_ptr_t value) : value_(value) {}

PrintExp::val_ptr_t &PrintExp::get_value() { return value_; }

void PrintExp::accept(Visitor &visitor) { visitor.visit(*this); }

/* AssignExp */

AssignExp::AssignExp(val_ptr_t lhs, val_ptr_t rhs) : lhs_(lhs), rhs_(rhs) {}

AssignExp::val_ptr_t &AssignExp::get_lhs() { return lhs_; }

AssignExp::val_ptr_t &AssignExp::get_rhs() { return rhs_; }

void AssignExp::accept(Visitor &visitor) { visitor.visit(*this); }

/* FunctionDec */

FunctionDec::FunctionDec(std::string name, exps_ptr_t exps)
    : name_(name), exps_(exps) {}

std::string &FunctionDec::get_name() { return name_; }

FunctionDec::exps_ptr_t &FunctionDec::get_exps() { return exps_; }

void FunctionDec::accept(Visitor &visitor) { visitor.visit(*this); }

/* FunctionCall */

FunctionCall::FunctionCall(std::string name) : name_(name) {}

std::string &FunctionCall::get_name() { return name_; }

FunctionCall::fdec_ptr_t FunctionCall::get_def() { return def_; }

void FunctionCall::accept(Visitor &visitor) { visitor.visit(*this); }

/* IfStmt */

IfStmt::IfStmt(value_ptr_t lhs, value_ptr_t rhs, exps_ptr_t exps)
    : lhs_(lhs), rhs_(rhs), exps_(exps) {}

IfStmt::IfStmt(IfStmt::value_ptr_t lhs, IfStmt::value_ptr_t rhs,
               IfStmt::exps_ptr_t exps, IfStmt::exps_ptr_t else_exps)
    : lhs_(lhs), rhs_(rhs), exps_(exps), else_exps_(else_exps) {}

IfStmt::value_ptr_t IfStmt::get_lhs() { return lhs_; }

IfStmt::value_ptr_t IfStmt::get_rhs() { return rhs_; }

IfStmt::exps_ptr_t IfStmt::get_exps() { return exps_; }

IfStmt::exps_ptr_t IfStmt::getElse_exps() { return else_exps_; }

void IfStmt::accept(Visitor &visitor) { visitor.visit(*this); }

RepeatStmt::RepeatStmt(RepeatStmt::value_ptr_t num, RepeatStmt::exps_ptr_t exps)
    : num_(num), exps_(exps) {}

RepeatStmt::value_ptr_t RepeatStmt::get_num() { return num_; }

RepeatStmt::exps_ptr_t RepeatStmt::get_exps() { return exps_; }

void RepeatStmt::accept(Visitor &visitor) { visitor.visit(*this); }