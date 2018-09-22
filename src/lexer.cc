#include <sys/types.h>
#include <regex.h>
#include <iostream>
#include <cstring>

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
  {DEQ, "=="},
  {NUMBER, "[0-9]\\+"},
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

std::vector<Token>
Lexer::scan(const std::string& input) {
  auto res = std::vector<Token>();
  std::stringstream ss = std::stringstream(input);
  std::string token;
  Token last_token = Token(Token::TEXT, "");
  bool found = false;
  bool pfound;
  skip_spaces(ss);
  while (ss.good()) {
    token = std::string();
    pfound = found;
    found = false;
    token += ss.get(); 
    for (auto it = Token::regexs_.begin(); it != Token::regexs_.end(); it++) {
      if (match(token, it->second)) {
        last_token = Token(it->first, token);
        found = true;
        break;
      }
    }
    if (!found && pfound) {
      res.push_back(last_token); 
      ss.seekp(-1);
      skip_spaces(ss);
      token = std::string();
    }
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


void
Lexer::skip_spaces(std::stringstream& ss) {
  while (ss.good() && is_space(ss.peek())) {
    ss.get(); 
  }
}

bool
Lexer::is_space(const char c) {
  for (const char *e = spaces_; e != nullptr; e++) {
    if (*e == c)
      return true;
  }
  return false;
}

std::string
Lexer::scan_enclosed_text(std::stringstream& ss, std::string begin,
                               std::string end) {
  if (!ss.good()) {
    throw std::invalid_argument("Empty string");
  }
  if (!compare(ss, begin)) {
    throw std::invalid_argument("String must begin with a '" + begin + "'");
  }
  std::string res = std::string(begin);
  bool escape = false;
  while (true) {
    if (!ss.good()) {
      throw std::invalid_argument("Unterminated string");
    }
    if (!escape && compare(ss, end)) {
      res += end;
      break;
    }
    char c = ss.get();
    if (!escape && c == '\\') {
      escape = true;
    }
    else if (escape) {
      escape = false;
    }
    
    if (!escape) {
      res += c;
    }
  }
  return res;
}

bool
Lexer::compare(std::stringstream& ss, std::string token) {
  for (size_t i = 0; i < token.length(); i++) {
    if (!ss.good()) {
      ss.seekp(-i);
      return false;
    }
    if (ss.get() != token.at(i)) {
      ss.seekp(-i - 1);
      return false;
    }
  }
  return true;
}
