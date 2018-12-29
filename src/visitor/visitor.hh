#pragma once

#include "../nodes/nodes.hh"

class Node;
class Exps;
class Exp;
class Value;
class PrintExp;
class AssignExp;
class FunctionDec;
class FunctionCall;
class IfStmt;
class RepeatStmt;

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
    virtual void visit(IfStmt& ifStmt);
    virtual void visit(RepeatStmt& repeatStmt);
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
    void visit(IfStmt& ifStmt) override;
    void visit(RepeatStmt& repeatStmt) override;
};
