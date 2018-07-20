#pragma once

#include <vector>
#include <string>
#include <memory>

#include "lexer.hh"
#include "nodes.hh"

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
};
