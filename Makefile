#JHolloway is writing this on FreeBSD, but it's go to compile on linux using GCC
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), FreeBSD)
	CXX = clang++
endif

ifeq ($(UNAME_S), Linux)
	CXX = g++
endif

# Compiler flags JHolloway is picky and like to use all of warnings!!
CXXFLAGS = -Wall -Wextra -std=c++17

#source fils
SOURCES = main.cpp \
    $(wildcard src/*.cpp)

# Object files (generated from source files)
OBJECTS = $(SOURCES:.cpp=.o)

# Output binary
BINARY = dragonSlayer

# Rule to link the binary
$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

# Rule to compile .cpp files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up the binary and object files
.PHONY: clean
clean:
	rm -rf $(BINARY) $(OBJECTS)

# Clean only the object files
.PHONY: clean-obj
clean-obj:
	rm -rf $(OBJECTS)
