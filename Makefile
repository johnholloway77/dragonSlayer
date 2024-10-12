# JHolloway is writing this on FreeBSD, but it's going to compile on Linux using GCC
UNAME_S := $(shell uname -s)


# Output binary
BINARY = dragonSlayer
GTEST_BINARY = test_${BINARY}


#directories
SRC_DIR = src
PROJECT_SRC_DIR = src/project
GTEST_INCLUDE_DIR = /usr/local/include
SRC_INCLUDE_DIR = ./include
GTEST_DIR = test
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(PROJECT_SRC_DIR)/*.cpp)


# Compiler variables and flags will depend if running on FreeBSD or Linux because John wants to learn cross compilation.
ifeq ($(UNAME_S), FreeBSD)
    CXX := clang++
    INCLUDE = -I ${SRC_INCLUDE_DIR} -I ${GTEST_INCLUDE_DIR}
else
    CXX := g++
    INCLUDE = -I ${SRC_INCLUDE_DIR}
endif
CXXFLAGS := -Wall -Wextra -std=c++17
DEBUG := -g -O0
LIBS := -lncurses
GTEST_LIB:= -lgtest
# Object files (generated from source files)
OBJECTS = $(SOURCES:.cpp=.o)
# Rule to link the binary
$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) ${LIBS}
# Rule to compile .cpp files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Tool variables
STATIC_ANALYSIS = cppcheck
STYLE_CHECK = cpplint
################################################################################
# Clean-up targets
################################################################################

# Clean up the binary and object files
.PHONY: clean
clean:
	rm -rf $(BINARY) $(OBJECTS) $(GTEST_BINARY)

# Clean only the object files
.PHONY: clean-obj
clean-obj:
	rm -rf $(OBJECTS)

# Clean only the executable files
.PHONY: clean-exec
clean-exec:
	rm -f $(GTEST_BINARY) $(BINARY)
################################################################################
# Test targets
################################################################################

${GTEST_BINARY}: ${GTEST_DIR}/*.cpp ${SRC_DIR}/*.cpp
	${CXX} $(CXXFLAGS) $(INCLUDE) -o $@ $^ -L/usr/local/lib ${GTEST_LIB} ${LIBS}

# To perform the static check
static:
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR} ${GTEST_DIR} \
	${SRC_INCLUDE_DIR} --suppress=missingInclude --error-exitcode=1

# To perform the style check
# excluding SRC_NCURSES_DIR as it was not made by project authors, but needed to be included directly to run on gitlab
style:
	${STYLE_CHECK} --recursive ${SRC_DIR}/* ${GTEST_DIR}/* ${SRC_INCLUDE_DIR}/*

#Check for memory leaks with Valgrind. Off to Valhalla we go!!
memcheck: ${GTEST}
	valgrind --tool=memcheck --leak-check=yes --error-exitcode=1 ./${GTEST_BINARY}

test: ${GTEST_BINARY}
	./${GTEST_BINARY}

compile: $(BINARY)

#debug for John to fight this program in gdb
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(BINARY)