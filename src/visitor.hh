#pragma once

#include "nodes.hh"

class Node;
class Exps;
class Exp;
class Value;
class PrintExp;
class AssignExp;
class FunctionDec;
class FunctionCall;

class Visitor {
  public:
    virtual void visit(const Node& node) const;
    virtual void visit(const Exps& exps) const;
    virtual void visit(const Exp& exp) const;
    virtual void visit(const Value& value) const;
    virtual void visit(const PrintExp& printExp) const;
    virtual void visit(const AssignExp& assignExp) const;
    virtual void visit(const FunctionDec& functionDec) const;
    virtual void visit(const FunctionCall& functionCall) const; 
};

class Printer : public Visitor {
  public:
    using Visitor::visit;

    void visit(const Exps& exps) const override;
    void visit(const Value& value) const override;
    void visit(const PrintExp& printExp) const override;
    void visit(const AssignExp& assignExp) const override;
    void visit(const FunctionDec& functionDec) const override;
    void visit(const FunctionCall& functionCall) const override; 
};
