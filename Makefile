cat > create_makefile.sh << 'EOF'
#!/bin/bash
cat > Makefile << 'MAKEFILE'
# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
DEBUGFLAGS = -g -DDEBUG

# Target executable
TARGET = leaderboard

# Source files
SRCS = main.cpp SkipList.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = SkipList.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild everything
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean rebuild run debug
MAKEFILE
EOF

chmod +x create_makefile.sh
./create_makefile.sh