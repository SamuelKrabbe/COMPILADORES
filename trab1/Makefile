# For Unix-like environments
# To use type 'make' to use the default function
# or 'make <function>' to use a specific function

PROG = principal.cpp scanner.cpp parser.cpp
HEADERS = scanner.h token.h parser.h
ORIGIN = analisadorLexico.exe
INPUT = input.mj

CFLAGS = -pedantic -Wall

all: compile run clean help

compile:
	@echo ""
	@echo "Compiling..."
	@echo ""
	@g++ $(PROG) $(HEADERS) -o $(ORIGIN) $(CFLAGS)

run: compile
	@echo ""
	@echo "Running..."
	@echo ""
	@./$(ORIGIN) $(INPUT)

clean:
	@echo ""
	@echo ""
	@echo "Cleaning..."
	@echo ""
	@rm -f $(ORIGIN)
	@echo "Origin file removed"
	@echo ""

help:
	@echo ""
	@echo "For more commands type: 'make commands'"
	@echo ""

commands:
	@echo ""
	@echo "type:"
	@echo "    'make compile' to compile"
	@echo ""
	@echo "    'make run' to run the compiled file"
	@echo ""
	@echo "    'make clean' to remove the origin (.exe) file"
	@echo ""

default:
	@echo "----------------------------------------------"
	@make compile
	@make run
	@make help
