SRC_DIR=src
BIN_DIR=bin

CXX=g++
CXX_FLAGS=-Wall

INCLUDE_FLAGS=-I$(SRC_DIR)

SRC=$(wildcard $(SRC_DIR)/*.cpp)

EXE=$(patsubst %.cpp, %, $(SRC))

all: exe move

exe: $(EXE)
	@for target in $(EXE); \
	do \
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -o $$target $$target.cpp; \
	done

move:
	$(shell mkdir -p $(BIN_DIR))
	$(shell mv $(EXE) $(BIN_DIR))

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)
	rm -f $(EXE)
