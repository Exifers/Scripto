#pragma once

#include <vector>
#include <string>
#include <map>
#include <sstream>

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
      DEQ,
      NUMBER,
      TEXT,
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
    void skip_spaces(std::stringstream& ss);
    bool is_space(const char c);
    std::string scan_enclosed_text(std::stringstream& ss, std::string begin,
                                   std::string end);
    bool compare(std::stringstream& ss, std::string token);
};
