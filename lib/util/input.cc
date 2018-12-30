#include <fstream>
#include <iostream>
#include <string>

#include "lib/util/input.hh"

std::string read_file(std::string filename) {
  std::ifstream ifs = std::ifstream(filename);
  std::string source = "";
  std::string str = "";
  while (ifs.good()) {
    std::getline(ifs, str);
    if (str[0] != '#') {
      source += str + "\n";
    }
  }
  return source;
}

std::string read_cin() {
  std::string source = "";
  while (true) {
    std::string str = std::string();
    if (std::cin.peek() == '\n') {
      std::cin.get();
      continue;
    } else if (std::cin.peek() == EOF) {
      break;
    }

    std::getline(std::cin, str);
    if (str[0] != '#') {
      source += str + "\n";
    }
  }
  return source;
}
