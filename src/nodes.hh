#pragma once

#include <string>
#include <vector>
#include <memory>

#include "visitor.hh"

class Exp;
class Visitor;

class Node {
  public:
    virtual void accept(const Visitor& visitor) const;
};

class Exps : public Node {
  public:
    using exp_ptr_t = std::shared_ptr<Exp>;
    using exp_vec_t = std::vector<exp_ptr_t>;
    Exps() = default;
    void add_exp(exp_ptr_t exp);
    const exp_vec_t& get_exps() const;

    void accept(const Visitor& visitor) const override;
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

    const std::string& get_name() const;
    const int& get_value() const;
    const value_t& get_type() const;

    void accept(const Visitor& visitor) const override;
  private:
    std::string name_;
    int value_;
    value_t type_;
};

class PrintExp : public Exp {
  public:
    using val_ptr_t = std::shared_ptr<Value>;
    PrintExp(val_ptr_t value);
    
    const val_ptr_t& get_value() const;

    void accept(const Visitor& visitor) const override;
  private:
    val_ptr_t value_;
};

class AssignExp : public Exp {
  public:
    using val_ptr_t = std::shared_ptr<Value>;
    AssignExp(val_ptr_t lhs, val_ptr_t rhs);
    
    const val_ptr_t& get_lhs() const;
    const val_ptr_t& get_rhs() const;

    void accept(const Visitor& visitor) const override;
  private:
    val_ptr_t lhs_;
    val_ptr_t rhs_; 
};

class FunctionDec : public Exp {
  public:
    using exps_ptr_t = std::shared_ptr<Exps>;
    FunctionDec(std::string name, exps_ptr_t exps);

    const std::string& get_name() const;
    const exps_ptr_t& get_exps() const;

    void accept(const Visitor& visitor) const override;
  private:
    std::string name_;
    exps_ptr_t exps_;
};

class FunctionCall : public Exp {
  public:
    using fdec_ptr_t = std::shared_ptr<FunctionDec>;
    FunctionCall(std::string name);

    const std::string& get_name() const;
    const fdec_ptr_t get_def() const;

    void accept(const Visitor& visitor) const override;
  private:
    std::string name_;
    fdec_ptr_t def_;
};
