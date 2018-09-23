
set(CXX_STANDARD 17)

add_executable(script.o2
        src/executer.cc
        src/lexer.cc
        src/main.cc
        src/nodes.cc
        src/parser.cc
        src/visitor.cc)
