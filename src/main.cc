#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <exception>
#include <memory>

#include "lexer.hh"
#include "parser.hh"
#include "visitor.hh"
#include "executer.hh"

class Main {
  public:
    static void run();
};

void
Main::run() {
  Lexer lexer = Lexer();
  Printer printer = Printer();
  (void) printer;
  Executer executer = Executer();
  std::string str;
  while (true) {
    str = std::string();
    if (std::cin.peek() == '\n') {
      std::cin.get();
      continue;
    }
    else if (std::cin.peek() == EOF) { break; }

    std::getline(std::cin, str);

    try {
      auto tokens = lexer.scan(str); 
      Parser parser = Parser(tokens);
      std::shared_ptr<Node> ast = parser.parse();
      //ast->accept(printer);
      //std::cout << std::endl;
      ast->accept(executer);
    }
    catch(const std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;
  std::cout << "Scripto V0.2" << std::endl;
  Main::run();
}
