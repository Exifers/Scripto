#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <exception>
#include <memory>
#include <fstream>

#include "lexer/lexer.hh"
#include "parser/parser.hh"
#include "visitor/visitor.hh"
#include "interpreter/interpreter.hh"
#include "lib/util/input.hh"

/**
 * @name Main
 * @details A class providing entry point for source code.
 */
class Main {
  public:
   /**
     * @name run
     * @details The entry point of the source code, performs all interpreting.
     * @param source the source code
     */
    static void run(std::string source);
};

void
Main::run(std::string source) {
  Lexer lexer = Lexer();
  Printer printer = Printer();
  (void) printer;
  Interpreter interpreter = Interpreter();
  try {
    auto tokens = lexer.scan(source);
    Parser parser = Parser(tokens);
    std::shared_ptr<Node> ast = parser.parse();
    //ast->accept(printer);
    //std::cout << std::endl;
    ast->accept(interpreter);
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

/**
 * @name main
 * @details main function. Reads code from standard input or given file and runs interpreter.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
  (void) argc;
  (void) argv;
  std::string source;
  if (argc >= 2) {
    source = read_file(argv[1]);
  }
  else {
    std::cout << "Scripto V0.2" << std::endl;
    source = read_cin();
  }
  Main::run(source);
}
