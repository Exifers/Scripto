#! /bin/sh

find src/ lib/ -type f -exec clang-format -i {} --style=llvm \;
