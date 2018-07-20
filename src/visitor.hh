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
    virtual void visit(Node& node) ;
    virtual void visit(Exps& exps) ;
    virtual void visit(Exp& exp) ;
    virtual void visit(Value& value) ;
    virtual void visit(PrintExp& printExp) ;
    virtual void visit(AssignExp& assignExp) ;
    virtual void visit(FunctionDec& functionDec) ;
    virtual void visit(FunctionCall& functionCall) ; 
};

class Printer : public Visitor {
  public:
    using Visitor::visit;

    void visit(Exps& exps) override;
    void visit(Value& value) override;
    void visit(PrintExp& printExp) override;
    void visit(AssignExp& assignExp) override;
    void visit(FunctionDec& functionDec) override;
    void visit(FunctionCall& functionCall) override; 
};
