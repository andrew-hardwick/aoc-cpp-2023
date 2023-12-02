.DEFAULT_GOAL := all

# CXX Configuration

CXX := g++
CXX_FLAGS := -Wall -O2 -std=c++17

# Manual Configuration

SRC_DIR := ./src
OBJ_DIR := ./obj
EXE_DIR := ./build

UTIL_DIR := ./utility
UTIL_LIB := aocUtility

# Automatic Configuration

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXE_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(EXE_DIR)/%.exe,$(SRC_FILES))

UTIL_SRC := $(wildcard $(UTIL_DIR)/src/*.cpp) $(wildcard $(UTIL_DIR)/inc/*.hpp)

INC_FLAGS := -I$(UTIL_DIR)/inc
LD_FLAGS := -L$(UTIL_DIR)/rel -l$(UTIL_LIB)

UTIL_LIB_A := $(UTIL_DIR)/rel/lib$(UTIL_LIB).a

# Recipes

.PRECIOUS: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(UTIL_LIB_A) | $(OBJ_DIR)
	$(CXX) $(CXX_FLAGS) $(INC_FLAGS) -c -o $@ $<

$(EXE_DIR)/%.exe: $(OBJ_DIR)/%.o $(UTIL_OBJS) | $(EXE_DIR)
	$(CXX) $(CXX_FLAGS) -o $@ $< $(UTIL_OBJS) $(LD_FLAGS) -L../utility/rel -laocUtility

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXE_DIR):
	mkdir -p $(EXE_DIR)

$(UTIL_LIB_A): $(UTIL_SRC)
	make -C $(UTIL_DIR)

all: $(EXE_FILES) 

clean:
	make -C $(UTIL_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -rf $(EXE_DIR)
