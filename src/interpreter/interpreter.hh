#pragma once

#include <map>
#include <memory>
#include <string>

#include "../visitor/visitor.hh"

class Interpreter : public Visitor {
public:
  using Visitor::visit;

  void visit(PrintExp &printExp) override;
  void visit(AssignExp &assignExp) override;
  void visit(FunctionDec &functionDec) override;
  void visit(FunctionCall &functionCall) override;
  void visit(IfStmt &ifStmt) override;
  void visit(RepeatStmt &repeatStmt) override;

private:
  std::map<std::string, int> int_values_;
  std::map<std::string, std::string> string_values_;
  std::map<std::string, std::shared_ptr<Node>> functions_;

  void set_int_value(std::string &name, int value);
  void set_string_value(std::string &name, std::string &value);

  std::shared_ptr<Node> read_function(FunctionCall &functionCall);
  void set_function(std::string &name, std::shared_ptr<Node> function);

  void resolve_value(std::shared_ptr<Value> value);
};
