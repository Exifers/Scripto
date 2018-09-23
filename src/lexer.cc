#include <sys/types.h>
#include <regex.h>
#include <iostream>
#include <cstring>
#include <iomanip>

#include "lexer.hh"

#define REGEX_ERR_BUF_SIZE 256

std::map<Token::token_t, std::string> Token::regexs_ =
{
  {LPAR, "("},
  {RPAR, ")"},
  {LCBRA, "{"},
  {RCBRA, "}"},
  {EQ, "="},
  {FUNCTION, "function"},
  {PRINT, "print"},
  {IF, "if"},
  {ELSE, "else"},
  {DEQ, "=="},
  {NUMBER, "[0-9]\\+"},
  {STRING, "\"[a-zA-Z0-9_][a-zA-Z0-9_]*\""},
  {NAME, "[a-zA-Z][a-zA-Z0-9]*"}
};

Token::Token(token_t type, std::string value)
  : type_(type), value_(value)
{}

const std::string&
Token::get_value() const {
  return value_;
}

const Token::token_t&
Token::get_type() const {
  return type_;
}

bool
Token::operator==(const Token& token) const {
  (void) token;
  return true;
}

bool
Token::operator!=(const Token& token) const {
  (void) token;
  return true;
}

std::string
Lexer::atohex(const char *input) {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (int i = 0; input[i] != 0; ++i)
  {
    ss << "\\0x" << static_cast<unsigned>(input[i]);
  }
  return ss.str();
}

std::vector<Token>
Lexer::scan(const std::string& input) {
  auto res = std::vector<Token>();

  bool found;
  char *token = strtok((char *) input.c_str(), spaces_);
  while (token != nullptr) {
    found = false;
    for (auto it = Token::regexs_.begin(); it != Token::regexs_.end(); it++) {
      if (match(std::string(token), it->second)) {
        res.push_back(Token(it->first, std::string(token))); 
        found = true;
        break;
      }
    }
    if (!found)
      throw std::invalid_argument(std::string("Unexpected token: ") + token + " (" + atohex(token) + ")");
    token = strtok(nullptr, spaces_);
  }
  
  return res;
}

bool
Lexer::match(const std::string& input, const std::string& simple_pattern) {
  regex_t preg;
  int error;
  if ((error = regcomp(&preg, ("^" + simple_pattern + "$").c_str(), 0)) != 0) {
    char error_buffer[REGEX_ERR_BUF_SIZE];
    regerror(error, &preg, error_buffer, REGEX_ERR_BUF_SIZE);
    std::cerr << error_buffer << std::endl;
    std::exit(1);
  }
  int res = regexec(&preg, input.c_str(), 0, nullptr, 0);     
  regfree(&preg);
  return res == 0;
}
