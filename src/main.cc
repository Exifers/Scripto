#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <exception>
#include <memory>
#include <fstream>

#include "lexer.hh"
#include "parser.hh"
#include "visitor.hh"
#include "executer.hh"

class Main {
  public:
    static void run(std::string source);
    static std::string read_file(std::string filename);
    static std::string read_cin();
};

void
Main::run(std::string source) {
  Lexer lexer = Lexer();
  Printer printer = Printer();
  (void) printer;
  Executer executer = Executer();
  try {
    auto tokens = lexer.scan(source);
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

std::string Main::read_cin() {
  std::string source;
  while (true) {
    std::string str = std::string();
    if (std::cin.peek() == '\n') {
      std::cin.get();
      continue;
    }
    else if (std::cin.peek() == EOF) { break; }

    std::getline(std::cin, str);
    if (str[0] != '#') {
      source += str + "\n";
    }
  }
  return source;
}

std::string Main::read_file(std::string filename) {
  std::ifstream ifs = std::ifstream(filename);
  std::string source;
  std::string str;
  while (ifs.good()) {
    std::getline(ifs, str);
    if (str[0] != '#') {
      source += str + "\n";
    }
  }
  return source;
}

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;
  std::string source;
  if (argc >= 2) {
    source = Main::read_file(argv[1]);
  }
  else {
    std::cout << "Scripto V0.2" << std::endl;
    source = Main::read_cin();
  }
  Main::run(source);
}