CC=g++
CXX_FLAGS=-Wall
INCLUDE_FLAGS=-Isrc

SRC=src/singlelinks.cpp
EXE=bin/singlelinks

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CXX_FLAGS) $(INCLUDE_FLAGS) -o $(EXE) $^

.PHONY: clean

clean:
	rm -f bin/*
