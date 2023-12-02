.DEFAULT_GOAL := all

# CXX Configuration

CXX := g++
CXX_FLAGS := -Wall -O2 -std=c++17

# Manual Configuration

NAME = aocUtility

SRC_DIR := ./src
INC_DIRS := ./inc
OBJ_DIR := ./obj
REL_DIR := ./rel

# Automatic Configuration

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

INC_FLAGS := $(patsubst %,-I%,$(INC_DIRS))

# Recipes

.PRECIOUS: $(OBJ_FILES)

all: $(OBJ_FILES) $(REL_INC) | $(REL_DIR)
	ar -rc $(REL_DIR)/lib$(NAME).a $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXX_FLAGS) $(INC_FLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(REL_DIR):
	mkdir -p $(REL_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(REL_DIR)
