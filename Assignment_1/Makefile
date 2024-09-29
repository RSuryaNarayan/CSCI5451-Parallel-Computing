# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Source files
SOURCES = $(wildcard *.cpp)

# Target executables (one for each source file)
TARGETS = $(SOURCES:.cpp=)

# Default target
all: $(TARGETS)

# Compile and link each source file to its own executable
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean up build artifacts
clean:
	rm -f $(TARGETS)

# Phony targets
.PHONY: all clean