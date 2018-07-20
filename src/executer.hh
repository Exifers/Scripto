#pragma once

#include "nodes.hh"

class Executer {
  public:
    void run(std::shared_ptr<Node> ast);
  private:
    std::map<std::string, int> values_;
};
