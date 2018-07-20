#pragma once

#include <string>
#include <map>
#include <memory>

#include "visitor.hh"

class Executer : public Visitor {
  public:
    using Visitor::visit;

    void visit(PrintExp& printExp) override;
    void visit(AssignExp& assignExp) override;
    void visit(FunctionDec& functionDec) override;
    void visit(FunctionCall& functionCall) override; 
  private:
    std::map<std::string, int> values_;
    std::map<std::string, std::shared_ptr<Node>> functions_;

    int read_value(Value& value);
    void set_value(std::string& name, int value);

    std::shared_ptr<Node> read_function(FunctionCall& functionCall);
    void set_function(std::string& name, std::shared_ptr<Node> function);
};
