#pragma once

#include <vector>
#include <string>
#include <map>

class Token {
  public: 
    typedef enum token {
      LPAR,
      RPAR,
      LCBRA,
      RCBRA,
      EQ,
      FUNCTION,
      PRINT,
      IF,
      ELSE,
      DEQ,
      NUMBER,
      STRING,
      NAME
    } token_t;
    static std::map<token_t, std::string> regexs_;
    
    Token(token_t type, std::string value);

    const token_t& get_type() const;
    const std::string& get_value() const;

    bool operator==(const Token& rhs) const;
    bool operator!=(const Token& rhs) const;
  private:
    token_t type_;
    std::string value_;
};

class Lexer {
  public:
    Lexer() = default;
    std::vector<Token> scan(const std::string& input);

    const char *spaces_ = " \n\t";

  private:
    bool match(const std::string& input, const std::string& simple_pattern);
    std::string atohex(const char *input);
};
