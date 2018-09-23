CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -I .

bin = main
fls = $(shell find src/ -type f -name "*.cc")
obj = $(addsuffix .o, $(basename $(fls)))

debug : CXXFLAGS += -g

all: $(obj)
	$(CXX) $(CXXFLAGS) $(obj) -o $(bin)

debug: $(obj)
	$(CXX) $(CXXFLAGS) $(obj) -o $(bin)	

clean:
	$(RM) $(bin) $(obj)
