#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../visitor/visitor.hh"

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
    typedef enum {
      LVALUE, // int or string
      RVALUE  // name
    } memory_t;
    typedef enum {
        INT,
        STRING,
        STRUCT,
        CLASS
    } type_t;
    Value(std::string value);
    Value(int value);
    Value(std::string name, std::string value);
    Value(std::string name, int value);

    std::string& get_name();
    int& get_int_value();
    memory_t& get_memory();
    type_t& get_type();
    std::string& get_string_value();

    void accept(Visitor& visitor) override;
  private:
    std::string name_;
    int int_value_;
    std::string string_value_;
    memory_t memory_;
    type_t type_;
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
    IfStmt(value_ptr_t lhs, value_ptr_t rhs, exps_ptr_t exps, exps_ptr_t else_exps);

    value_ptr_t get_lhs();
    value_ptr_t get_rhs();
    exps_ptr_t get_exps();
    exps_ptr_t getElse_exps();

    void accept(Visitor& visitor) override;
  private:
    value_ptr_t lhs_;
    value_ptr_t rhs_;
    exps_ptr_t exps_;
    exps_ptr_t else_exps_;
};

class RepeatStmt : public Exp {
public:
    using exps_ptr_t = std::shared_ptr<Exps>;
    using value_ptr_t = std::shared_ptr<Value>;
    RepeatStmt(value_ptr_t num, exps_ptr_t exps);

    value_ptr_t get_num();
    exps_ptr_t get_exps();

    void accept(Visitor& visitor) override;
private:
    value_ptr_t num_;
    exps_ptr_t exps_;
};