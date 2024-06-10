# For Unix-like environments
# To use type 'make' to use the default function
# or 'make <function>' to use a specific function

PROG = *.cpp
HEADERS = scanner.h token.h parser.h
ORIGIN = mj_compiler
INPUT = input.mj

CFLAGS = -pedantic -Wall

all: compile run help

compile:
	@echo Compilando...
	@g++ $(PROG) -o $(ORIGIN)

run: compile
	@./$(ORIGIN) $(INPUT)

clean:
	@echo Limpando...
	@rm -f $(ORIGIN)
	@echo Arquivo origem removido

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
