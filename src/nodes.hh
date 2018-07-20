#pragma once

#include <string>
#include <vector>
#include <memory>

#include "visitor.hh"

class Exp;
class Visitor;

class Node {
  public:
    virtual void accept(Visitor& visitor);
};

class Exps : public Node {
  public:
    using exp_ptr_t = std::shared_ptr<Exp>;
    using exp_vec_t = std::vector<exp_ptr_t>;
    Exps() = default;
    void add_exp(exp_ptr_t exp);
    exp_vec_t& get_exps();

    void accept(Visitor& visitor) override;
  private:
    exp_vec_t exps_ = exp_vec_t();
};

class Exp : public Node {
};

class Value : public Node {
  public:
    typedef enum type {
      VARIABLE,
      STATIC
    } value_t;
    Value(std::string name);
    Value(int value);

    std::string& get_name();
    int& get_value();
    value_t& get_type();

    void accept(Visitor& visitor) override;
  private:
    std::string name_;
    int value_;
    value_t type_;
};

class PrintExp : public Exp {
  public:
    using val_ptr_t = std::shared_ptr<Value>;
    PrintExp(val_ptr_t value);
    
    val_ptr_t& get_value();

    void accept(Visitor& visitor) override;
  private:
    val_ptr_t value_;
};

class AssignExp : public Exp {
  public:
    using val_ptr_t = std::shared_ptr<Value>;
    AssignExp(val_ptr_t lhs, val_ptr_t rhs);
    
    val_ptr_t& get_lhs();
    val_ptr_t& get_rhs();

    void accept(Visitor& visitor) override;
  private:
    val_ptr_t lhs_;
    val_ptr_t rhs_; 
};

class FunctionDec : public Exp {
  public:
    using exps_ptr_t = std::shared_ptr<Exps>;
    FunctionDec(std::string name, exps_ptr_t exps);

    std::string& get_name();
    exps_ptr_t& get_exps();

    void accept(Visitor& visitor) override;
  private:
    std::string name_;
    exps_ptr_t exps_;
};

class FunctionCall : public Exp {
  public:
    using fdec_ptr_t = std::shared_ptr<FunctionDec>;
    FunctionCall(std::string name);

    std::string& get_name();
    fdec_ptr_t get_def();

    void accept(Visitor& visitor) override;
  private:
    std::string name_;
    fdec_ptr_t def_;
};

class IfStmt : public Exp {
  public:
    using exps_ptr_t = std::shared_ptr<Exps>;
    using value_ptr_t = std::shared_ptr<Value>;
    IfStmt(value_ptr_t lhs, value_ptr_t rhs, exps_ptr_t exps);

    value_ptr_t get_lhs();
    value_ptr_t get_rhs();
    exps_ptr_t get_exps();

    void accept(Visitor& visitor) override;
  private:
    value_ptr_t lhs_;
    value_ptr_t rhs_;
    exps_ptr_t exps_;
};

