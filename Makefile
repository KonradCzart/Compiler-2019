CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wno-sign-compare -g

BIN		:= bin
SRC		:= src
INCLUDE	:= include
PARSER 	:= parser

LIBRARIES	:=

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= compilator.exe
else
EXECUTABLE	:= compilator
endif

all: subsystem $(BIN)/$(EXECUTABLE)

subsystem:
	$(MAKE) -C $(PARSER)

$(BIN)/$(EXECUTABLE): $(PARSER)/lex.yy.cc $(PARSER)/parser.tab.cc $(SRC)/*
	$(CC) $(C_FLAGS) -I $(INCLUDE) -I $(PARSER) $^ -o $@ $(LIBRARIES)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)
	$(RM) $(PARSER)/*.hh
	$(RM) $(PARSER)/*.cc

run: all
	./$(BIN)/$(EXECUTABLE)