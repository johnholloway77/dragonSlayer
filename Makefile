# JHolloway is writing this on FreeBSD, but it's going to compile on Linux using GCC
UNAME_S := $(shell uname -s)

# Detect platform and set CXX accordingly
ifeq ($(UNAME_S), FreeBSD)
    CXX := clang++
else
    CXX := g++
endif

# Compiler flags (JHolloway is picky and likes to use all of the warnings!!)
CXXFLAGS := -Wall -Wextra -std=c++17

#debug stuff since John keeps getting segfaults
DEBUG := -g -O0

# Source files (main.cpp and all .cpp files in the src directory)
SOURCES = main.cpp \
    $(wildcard src/*.cpp)

# Object files (generated from source files)
OBJECTS = $(SOURCES:.cpp=.o)

#libraries to link
LIBS := -lncurses

# Output binary
BINARY = dragonSlayer

# Rule to link the binary
$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) ${LIBS}

# Rule to compile .cpp files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#debug for John to fight this program in gdb
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(BINARY)

# Clean up the binary and object files
.PHONY: clean
clean:
	rm -rf $(BINARY) $(OBJECTS)

# Clean only the object files
.PHONY: clean-obj
clean-obj:
	rm -rf $(OBJECTS)


################################################################################
# Test targets
################################################################################

#directories
SRC_DIR = src
SRC_INCLUDE = include
GTEST_DIR = test

INCLUDE = -I ${SRC_INCLUDE}

# Tool variables
STATIC_ANALYSIS = cppcheck
STYLE_CHECK = cpplint

# To perform the static check 
static:
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR} ${GTEST_DIR} \
	${SRC_INCLUDE} --suppress=missingInclude --error-exitcode=1

# To perform the style check
style:
	${STYLE_CHECK} --recursive ${SRC_DIR}/* ${GTEST_DIR}/* ${SRC_INCLUDE}/*