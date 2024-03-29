#include "parser.h"
#include <string>

Parser::Parser(string input)
{
	scanner = new Scanner(input);
    advance();
}

void
Parser::run()
{
    prog();
}

void
Parser::advance()
{
	lookahead = scanner->nextToken();
    cout << lookahead->lexeme << " ";
}

void
Parser::match(int t, string keyword = "")
{
	if (lookahead->name == t || lookahead->attribute == t || lookahead->lexeme.compare(keyword) == 0) {
		advance();
	}
	else
		error("Erro inesperado");
}

// PROG   -> MAIN {CLASSE}
void 
Parser::prog()
{
	main();
	if (lookahead->lexeme.compare("class") == 0)
		classe();
}

// MAIN   -> class id '{' public static void main '(' String '[' ']' id ')' '{' CMD '}' '}'
void 
Parser::main()
{
	match(-1, "class");
	match(ID);
	match(LCHAVE);
	match(-1, "public");
	match(-1, "static");
	match(-1, "void");
	match(-1, "main");
	match(LPAR);
	match(-1, "String");
	match(LCOL);
	match(RCOL);
	match(ID);
	match(RPAR);
	match(LCHAVE);
	cmd();
	match(RCHAVE);
	match(RCHAVE);
}

// CLASSE -> class id [extends id] '{' {VAR} {METODO} '}'
void 
Parser::classe()
{
	match(-1, "class");
	match(ID);
	if (lookahead->lexeme.compare("extends") == 0) {
		match(ID);
	}
	match(LCHAVE);
	if (lookahead->lexeme.compare("}") != 0) {
		if (lookahead->lexeme.compare("int") == 0 || lookahead->lexeme.compare("boolean") == 0) {
            var();
        }
		if (lookahead->lexeme.compare("public") == 0) {
            metodo();
        }
	}
	match(RCHAVE);
}

// VAR    -> TIPO id ;
void 
Parser::var()
{
	tipo();
	match(ID);
	match(PONTO_VIRGULA);
}

// METODO -> public TIPO id '(' [PARAMS] ')' '{' {VAR} {CMD} return EXP ; '}'
void 
Parser::metodo()
{
	match(-1, "public");
	tipo();
	match(ID);
	match(LPAR);
	if (lookahead->lexeme.compare(")") != 0) {
		if (lookahead->lexeme.compare("int") == 0 || lookahead->lexeme.compare("boolean") == 0) {
        	params();
    	}
	}
	match(RPAR);
	match(LCHAVE);
	if (lookahead->lexeme.compare("}") != 0) {
		if (lookahead->lexeme.compare("int") == 0 || lookahead->lexeme.compare("boolean") == 0) {
            var();
        }
		if (lookahead->lexeme.compare("{") == 0 || lookahead->lexeme.compare("if") == 0 || lookahead->lexeme.compare("while") == 0 || lookahead->lexeme.compare("System.out.println") == 0) {
            cmd();
        }
	}
	match(-1, "return");
	exp();
	match(PONTO_VIRGULA);
	match(RCHAVE);
}

// PARAMS -> TIPO id {, TIPO id}
void 
Parser::params()
{
	tipo();
	match(ID);
	if (lookahead->lexeme.compare(",") == 0) {
		match(VIRGULA);
		tipo();
		match(ID);
	}
}

// TIPO   -> int '[' ']'
//         | boolean
//         | int
//         | id
void 
Parser::tipo()
{
	if (lookahead->lexeme.compare("int") == 0) {
		match(-1, "int");
		if (lookahead->lexeme.compare("[") == 0) {
			match(-1, "[");
			match(RCOL);
		}
	}
	else if (lookahead->lexeme.compare("boolean") == 0) {
		match(-1, "boolean");
	}
	else
		match(ID);
}

// CMD    -> '{' {CMD} '}'
//         | if '(' EXP ')' CMD
//         | if '(' EXP ')' CMD else CMD
//         | while '(' EXP ')' CMD
//         | System.out.println '(' EXP ')' ;
//         | id = EXP ;
//         | id '[' EXP ']' = EXP ;
void 
Parser::cmd()
{
	if (lookahead->lexeme.compare("{") == 0) {
		match(-1, "{");
        cmd();
		match(-1, "}");
    }
	else if (lookahead->lexeme.compare("if") == 0 || lookahead->lexeme.compare("while") == 0) {
		match(-1, "(");
        exp();
		match(-1, ")");
		cmd();
		if (lookahead->lexeme.compare("else") == 0) {
			match(-1, "else");
        	cmd();
    	}
	}
	else if (lookahead->lexeme.compare("System.out.println") == 0) {
		match(-1, "(");
        exp();
		match(-1, ")");
		match(PONTO_VIRGULA);
	}
	else {
		match(ID);
		if (lookahead->lexeme.compare("[") == 0) {
			match(-1, "[");
			exp();
			match(-1, "]");
		}
		match(-1, "=");
		exp();
		match(PONTO_VIRGULA);
	}
}

// EXP    -> EXP && REXP
//         | REXP
void 
Parser::exp()
{
	rexp();

    while (lookahead->lexeme.compare("&&") == 0) {
        match(AND);
        rexp();
    }
}

// REXP   -> REXP < AEXP
//         | REXP == AEXP
//         | REXP != AEXP
//         | AEXP
void 
Parser::rexp()
{
	aexp();

    if (lookahead->lexeme.compare("<") == 0) {
        match(LT);
		aexp();
    }
	else if (lookahead->lexeme.compare("==") == 0) {
        match(EQ);
		aexp();
    }
	else if (lookahead->lexeme.compare("!=") == 0) {
        match(DIFF);
		aexp();
    }
}

// AEXP   -> AEXP + MEXP
//         | AEXP - MEXP
//         | MEXP
void 
Parser::aexp()
{
	mexp();

	if (lookahead->lexeme.compare("+") == 0) {
        match(PLUS);
		mexp();
    }
	else if (lookahead->lexeme.compare("-") == 0) {
        match(MINUS);
		mexp();
    }
}

// MEXP   -> MEXP * SEXP
//         | MEXP / SEXP
//         | SEXP
void 
Parser::mexp()
{
	sexp();

	if (lookahead->lexeme.compare("*") == 0) {
        match(MULT);
		sexp();
    }
	else if (lookahead->lexeme.compare("/") == 0) {
        match(DIV);
		sexp();
    }
}

// SEXP   -> ! SEXP
//         | - SEXP
//         | true
//         | false
//         | num
//         | new int '[' EXP ']'
//         | PEXP . length
//         | PEXP '[' EXP ']'
//         | PEXP
void 
Parser::sexp()
{
	if (lookahead->lexeme.compare("!") == 0) {
        match(NOT);
        sexp();
    }
    else if (lookahead->lexeme.compare("-") == 0) {
        match(MINUS);
        sexp();
    }
    else if (lookahead->lexeme.compare("true") == 0 || lookahead->lexeme.compare("false") == 0 || lookahead->lexeme.compare("num") == 0) {
        match(-1, lookahead->lexeme); // Consome "true", "false" ou "num"
    }
    else if (lookahead->lexeme.compare("new") == 0) {
        match(-1, lookahead->lexeme); // Consome "new"
        match(-1, "int");
        match(LCOL);
        exp();
        match(RCOL);
    }
    else {
        pexp();
        if (lookahead->lexeme.compare(".") == 0) {
            match(PONTO);
            match(-1, "length");
        }
        else if (lookahead->lexeme.compare("[") == 0) {
            match(LCOL);
            exp();
            match(RCOL);
        }
    }
    // else {
    //     error("Erro inesperado");
    // }
}

// PEXP   -> id
//         | this
//         | new id '(' ')'
//         | '(' EXP ')'
//         | PEXP . id
//         | PEXP . id '(' [EXPS] ')'
void 
Parser::pexp()
{
	if (lookahead->lexeme.compare("id") == 0) {
        match(ID);
    }
    else if (lookahead->lexeme.compare("this") == 0) {
        match(-1, lookahead->lexeme);
    }
    else if (lookahead->lexeme.compare("new") == 0) {
        match(-1, lookahead->lexeme); // Consome "new"
        match(ID);
        match(LPAR);
        match(RPAR);
    }
    else if (lookahead->lexeme.compare("(") == 0) {
        match(-1, lookahead->lexeme);
        exp();
        match(RPAR);
    }
    else if (lookahead->lexeme.compare(".") == 0) {
        pexp();
        match(-1, lookahead->lexeme);
        match(ID);
        if (lookahead->lexeme.compare("(") == 0) {
            match(LPAR);
            if (lookahead->lexeme.compare(")") != 0) {
                exps();
            }
            match(RPAR);
        }
    }
	// else {
    //     error("Erro inesperado");
    // }
}

// EXPS   -> EXP {, EXP}
void 
Parser::exps()
{
	exp();
	if (lookahead->lexeme.compare(",") == 0) {
		match(VIRGULA);
		exp();
	}
}

void
Parser::error(string str)
{
	cout << endl << endl << str << endl;

	exit(EXIT_FAILURE);
}