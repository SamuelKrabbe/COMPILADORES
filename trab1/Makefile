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
	@echo Compiling...
	@g++ $(PROG) $(HEADERS) -o $(ORIGIN) $(CFLAGS)

run: compile
	@echo Running...
	@./$(ORIGIN) $(INPUT)

clean:
	@echo Cleaning...
	@rm -f $(ORIGIN)
	@echo Origin file removed

help:
	@echo For more commands type: 'make commands'

commands:
	@echo type:
	@echo     'make compile' to compile
	@echo     'make run' to run the compiled file
	@echo     'make clean' to remove the origin (.exe) file

default:
	@echo ------------------------------------------------
	@make run
	@make help
