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

# Linker flags
LDFLAGS = `pkg-config --libs raylib`

# Default target
all: dirs $(TARGET)

# Create directories if they don't exist
dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Linking rule
$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

# Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the game
run: all
	./$(TARGET)

# Debug target: builds with debug symbols and starts gdb
debug: CXXFLAGS += -g
debug: clean dirs all
	@echo "Starting GDB..."
	gdb -ex run --args ./$(TARGET)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)