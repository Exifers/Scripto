#include <iostream>
#include <memory>

#include "parser.hh"

Parser::Parser(std::vector<Token> tokens)
  : i_(0), tokens_(tokens)
{}

std::shared_ptr<Node>
Parser::parse() {
  return parse_exps();
}

std::shared_ptr<Exps>
Parser::parse_exps() {
  auto exps = std::make_shared<Exps>(); 

  while (has_next() && next().get_type() != Token::RCBRA) {
    switch(next().get_type()) {
      case Token::PRINT:
        exps->add_exp(parse_print());         
        break;
      case Token::NAME:
        exps->add_exp(parse_name());
        break;
      case Token::FUNCTION:
        exps->add_exp(parse_function_dec());
        break;
      default:
        throw std::invalid_argument(
          std::string("Unexpected token at beginning of expression: ")
        + next().get_value());
    }
  }
  return exps;
}

std::shared_ptr<PrintExp>
Parser::parse_print() {
  eat(Token::PRINT);
  try {
    auto val = std::make_shared<Value>(std::stoi(next().get_value()));
    step();
    return std::make_shared<PrintExp>(val);
  }
  catch(std::invalid_argument& e) {
    auto val = std::make_shared<Value>(next().get_value());
    step();
    return std::make_shared<PrintExp>(val);
  }
}

std::shared_ptr<Exp>
Parser::parse_name() {
  auto val = std::make_shared<Value>(next().get_value());
  step();
  switch(next().get_type()) {
    case Token::EQ: { // assignExp
      step();
      std::string value = next().get_value();
      try {
        auto rhs = std::make_shared<Value>(std::stoi(value));
        step();
        return std::make_shared<AssignExp>(val, rhs); 
      }
      catch(std::invalid_argument& e) {
        auto rhs = std::make_shared<Value>(value);
        step();
        return std::make_shared<AssignExp>(val, rhs); 
      }
    }
    case Token::LPAR: // functionCall
      step();
      step();
      return std::make_shared<FunctionCall>(val->get_name());
    default:
      throw std::invalid_argument("Expected '=' or '(' after name");
  }
}

std::shared_ptr<FunctionDec>
Parser::parse_function_dec() {
  eat(Token::FUNCTION);
  auto function_name = next().get_value();
  step();
  eat(Token::LCBRA);
  auto exps = parse_exps();
  eat(Token::RCBRA);
  return std::make_shared<FunctionDec>(function_name, exps);
}

void
Parser::eat(Token::token_t token) {
  if ((size_t) i_ == tokens_.size())
    throw std::invalid_argument(std::string("Unexpected end of file"));
  if (token != tokens_[i_].get_type())
    throw std::invalid_argument(std::string("Unexpected token: ")
      + tokens_[i_].get_value() + ", expected token of type: "
      + std::to_string(token));
  i_++;
}

void
Parser::step() {
  if ((size_t) i_ == tokens_.size())
    throw std::invalid_argument(std::string("Unexpected end of file"));
  i_++;
}

Token
Parser::next() const {
  if ((size_t) i_ == tokens_.size())
    throw std::invalid_argument(std::string("Unexpected end of file"));
  return tokens_[i_];
}

bool
Parser::has_next() const {
  return (size_t) i_ < tokens_.size();
}
