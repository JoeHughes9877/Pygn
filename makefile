CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TARGET := pign

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
