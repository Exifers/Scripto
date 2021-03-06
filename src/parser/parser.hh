#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../lexer/lexer.hh"
#include "../nodes/nodes.hh"

class Exp;

class Parser {
public:
  Parser(std::vector<Token> tokens);
  std::shared_ptr<Node> parse();

private:
  int i_;
  std::vector<Token> tokens_;

  void eat(Token::token_t);
  Token next() const;
  bool has_next() const;
  void step();

  std::shared_ptr<Exps> parse_exps();
  std::shared_ptr<PrintExp> parse_print();
  std::shared_ptr<Exp> parse_name();
  std::shared_ptr<FunctionDec> parse_function_dec();
  std::shared_ptr<IfStmt> parse_if();
  std::shared_ptr<Value> parse_value();
  std::shared_ptr<RepeatStmt> parse_repeat();
  std::shared_ptr<Value> parse_num();
};
