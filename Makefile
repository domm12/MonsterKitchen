# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Source and build directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Executable name
TARGET = $(BIN_DIR)/kitchen

# Linker flags with explicit libraries
LDFLAGS = `pkg-config --libs raylib`

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the game
run: all
	./$(TARGET)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)