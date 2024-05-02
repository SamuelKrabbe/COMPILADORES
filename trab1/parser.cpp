#include "parser.h"
#include <string>

Parser::Parser(string input)
{
	scanner = new Scanner(input);
	allocVetor();
    advance();
}

void
Parser::run()
{
    prog();
	freeVetor();
}

void
Parser::advance()
{
	lookahead = scanner->nextToken();
	printToken(lookahead);
    // cout << lookahead->lexeme << " ";
}

void
Parser::match(int t, string keyword = "")
{
	if (lookahead->name == t || lookahead->attribute == t || lookahead->lexeme.compare(keyword) == 0) {
		advance();
	}
	else {
		error("Erro inesperado");
	}
}

// PROG   -> MAIN {CLASSE}
void 
Parser::prog()
{
	cout << "prog" << " ";
	main();
	while (lookahead->lexeme.compare("class") == 0)
		classe();
}

// MAIN   -> class id '{' public static void main '(' String '[' ']' id ')' '{' CMD '}' '}'
void 
Parser::main()
{
	cout << "main" << " ";
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
	cout << "classe" << " ";
	match(-1, "class");
	match(ID);
	if (lookahead->lexeme.compare("extends") == 0) {
		match(-1, "extends");
		match(ID);
	}
	match(LCHAVE);
	if (lookahead->lexeme.compare("'}'") != 0) {
		while (lookahead->lexeme.compare("int") == 0 || lookahead->lexeme.compare("boolean") == 0 || lookahead->name == 1) {
            var();
        }
		while (lookahead->lexeme.compare("public") == 0) {
            metodo();
        }
	}
	match(RCHAVE);
}

// VAR    -> TIPO id ;
void 
Parser::var()
{
	cout << "var" << " ";
	tipo();
	match(ID);
	match(PONTO_VIRGULA);
	
}

// METODO -> public TIPO id '(' [PARAMS] ')' '{' {VAR} {CMD} return EXP ; '}'
void 
Parser::metodo()
{
	cout << "metodo" << " ";
	match(-1, "public");
	tipo();
	match(ID);
	match(LPAR);
	if (lookahead->lexeme.compare("')'") != 0) {
		if (lookahead->lexeme.compare("int") == 0 || lookahead->lexeme.compare("boolean") == 0 || lookahead->name == 1) {
        	params();
    	}
	}
	match(RPAR);
	match(LCHAVE);
	if (lookahead->lexeme.compare("'}'") != 0) {
		while (lookahead->lexeme.compare("int") == 0 || lookahead->lexeme.compare("boolean") == 0) {
            var();
        }
		while (lookahead->lexeme.compare("'{'") == 0 || lookahead->lexeme.compare("if") == 0 || lookahead->lexeme.compare("while") == 0 || lookahead->lexeme.compare("System.out.println") == 0) {
            cmd();
        }
		while (lookahead->name == 1) {
			id();
		}
		if (lookahead->lexeme.compare("return") == 0) {
			match(-1, "return");
			exp();
			match(PONTO_VIRGULA);
		}
	}
	match(RCHAVE);
}

void 
Parser::id()
{
	cout << "id" << " ";
	tipo();
	if (lookahead->lexeme.compare("=") == 0 || lookahead->lexeme.compare("'['") == 0) {
		id_();
	}
}

// PARAMS -> TIPO id {, TIPO id}
void 
Parser::params()
{
	cout << "params" << " ";
	tipo();
	match(ID);
	while (lookahead->lexeme.compare("','") == 0) {
		match(VIRGULA);
		tipo();
		match(ID);
	}
	
}

// TIPO   -> int INT_
//         | boolean
//         | id
void 
Parser::tipo()
{
	cout << "tipo" << " ";
	if (lookahead->lexeme.compare("int") == 0) {
		match(-1, "int");
		if (lookahead->lexeme.compare("'['") == 0) {
			match(-1, "'['");
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
//         | if '(' EXP ')' CMD ELSE_
//         | while '(' EXP ')' CMD
//         | System.out.println '(' EXP ')' ;
//         | id ID_
void 
Parser::cmd()
{
	cout << "cmd" << " ";
	if (lookahead->lexeme.compare("'{'") == 0) {
		match(-1, "'{'");
        cmd();
		match(-1, "'}'");
    }
	else if (lookahead->lexeme.compare("if") == 0) {
		match(-1, "if");
		match(-1, "'('");
        exp();
		match(-1, "')'");
		cmd();
		else_();
	}
	else if (lookahead->lexeme.compare("while") == 0) {
		match(-1, "while");
		match(-1, "'('");
        exp();
		match(-1, "')'");
		cmd();
	}
	else if (lookahead->lexeme.compare("System.out.println") == 0) {
		match(-1, "System.out.println");
		match(-1, "'('");
        exp();
		match(-1, "')'");
		match(PONTO_VIRGULA);
	}
	else {
		match(ID);
		id_();
	}
	
}

// ELSE_   -> else CMD
//         | epsilon
void 
Parser::else_()
{
	cout << "else_" << " ";
	if (lookahead->lexeme.compare("else") == 0) {
		match(-1, "else");
        cmd();
    }
	
}

// ID_   -> = EXP ;
//        | '[' EXP ']' = EXP ;
void 
Parser::id_()
{
	cout << "id_" << " ";
	if (lookahead->lexeme.compare("'['") == 0) {
		match(-1, "'['");
		exp();
		match(-1, "']'");
	}
	match(ATROP);
	exp();
	match(PONTO_VIRGULA);
}

// EXP    -> REXP EXP_
void 
Parser::exp()
{
	cout << "exp" << " ";
	rexp();
	exp_();
}

// EXP_   -> && REXP EXP_
//         | epsilon
void 
Parser::exp_()
{
	cout << "exp_" << " ";
	if (lookahead->lexeme.compare("&&") == 0) {
		rexp();
		exp_();
	}
}

// REXP   -> AEXP REXP_
void 
Parser::rexp()
{
	cout << "rexp" << " ";
	aexp();
	rexp_();
}

// REXP_   -> < AEXP REXP_
//         | == AEXP REXP_
//         | != AEXP REXP_
//         | epsilon
void 
Parser::rexp_()
{
	cout << "rexp_" << " ";
	if (lookahead->lexeme.compare("<") == 0) {
        match(LT);
		aexp();
		rexp_();
    }
	else if (lookahead->lexeme.compare("==") == 0) {
        match(EQ);
		aexp();
		rexp_();
    }
	else if (lookahead->lexeme.compare("!=") == 0) {
        match(DIFF);
		aexp();
		rexp_();
    }
	
}

// AEXP   -> MEXP AEXP_
void 
Parser::aexp()
{
	cout << "aexp" << " ";
	mexp();
	aexp_();
}

// AEXP_   -> + MEXP AEXP_
//         | - MEXP AEXP_
//         | epsilon
void 
Parser::aexp_()
{
	cout << "aexp_" << " ";
	if (lookahead->lexeme.compare("+") == 0) {
        match(PLUS);
		mexp();
		aexp_();
    }
	else if (lookahead->lexeme.compare("-") == 0) {
        match(MINUS);
		mexp();
		aexp_();
    }
	
}

// MEXP   -> SEXP MEXP_
void 
Parser::mexp()
{
	cout << "mexp" << " ";
	sexp();
	mexp_();
}

// MEXP_   -> * SEXP MEXP_
//         | / SEXP MEXP_
//         | epsilon
void 
Parser::mexp_()
{
	cout << "mexp_" << " ";
	if (lookahead->lexeme.compare("*") == 0) {
        match(MULT);
		sexp();
		mexp_();
    }
	else if (lookahead->lexeme.compare("/") == 0) {
        match(DIV);
		sexp();
		mexp_();
    }
	
}

// SEXP   -> ! SEXP
//         | - SEXP
//         | true
//         | false
//         | INTEGER_LITERAL
//		   | PEXP SEXP_
void 
Parser::sexp()
{
	cout << "sexp" << " ";
	if (lookahead->lexeme.compare("!") == 0) {
        match(NOT);
        sexp();
    }
    else if (lookahead->lexeme.compare("-") == 0) {
        match(MINUS);
        sexp();
    }
    else if (lookahead->lexeme.compare("true") == 0 || lookahead->lexeme.compare("false") == 0) {
        match(-1, lookahead->lexeme); // Consome "true", "false"
    }
	else if (isNumber(lookahead->lexeme) == 0) {
        match(INTEGER_LITERAL);
    }
    else if (lookahead->lexeme.compare("new") == 0) {
        pexp();
        sexp_();
    }
}

// SEXP_   -> . length
//         | '[' EXP ']'
//         | epsilon
void 
Parser::sexp_()
{
	cout << "sexp_" << " ";
	if (lookahead->lexeme.compare("'.'") == 0) {
        match(PONTO);
        match(-1, "length");
    }
    else if (lookahead->lexeme.compare("'['") == 0) {
        match(LCOL);
        exp();
        match(RCOL);
    }
	
}

// PEXP   -> id PEXP_
//         | this PEXP_
//         | new NEW_
//         | '(' EXP ')' PEXP_
void 
Parser::pexp()
{
	cout << "pexp" << " ";
    if (lookahead->lexeme.compare("this") == 0) {
        match(-1, "this");
		pexp_();
    }
    else if (lookahead->lexeme.compare("new") == 0) {
        match(-1, "new");
        new_();
    }
    else if (lookahead->lexeme.compare("'('") == 0) {
        match(LPAR);
        exp();
        match(RPAR);
		pexp_();
    }
	else {
        match(ID);
		pexp_();
    }
	
}

//NEW_ -> id '(' ')'
//     | int '[' EXP ']'
void 
Parser::new_()
{
	cout << "new_" << " ";
	if (lookahead->name == 1) {
		match(ID);
        match(LPAR);
        match(RPAR);
	} else if (lookahead->lexeme.compare("int") == 0) {
		match(-1, "int");
        match(LCOL);
        exp();
        match(RCOL);
	} else {
		error("Erro inesperado");
	}
	
}

// PEXP_   -> . id PEXP_PID
//         | epsilon
void 
Parser::pexp_()
{
	cout << "pexp_" << " ";
	if (lookahead->lexeme.compare("'.'") == 0) {
		match(PONTO);
		match(ID);
        pexp_pid();
    }
	
}

// PEXP_PID-> '(' [EXPS] ')'
//         | epsilon
void 
Parser::pexp_pid()
{
	cout << "pexp_pid" << " ";
    if (lookahead->lexeme.compare("'('") == 0) {
        match(LPAR);
        if (lookahead->lexeme.compare("')'") != 0) {
            exps();
        }
        match(RPAR);
    }
}

// EXPS   -> EXP {, EXP}
void 
Parser::exps()
{
	cout << "exps" << " ";
	exp();
	while (lookahead->lexeme.compare("','") == 0) {
		match(VIRGULA);
		exp();
	}
	
}

void
Parser::allocVetor()
{
    vet = new string[29];

    vet[0] = "UNDEF";//0
    vet[1] = "ID";//1
    vet[2] = "INTEGER_LITERAL";//2
    vet[3] = "OP";//3
    vet[4] = "AND";//4
    vet[5] = "LT";//5
    vet[6] = "GT";//6
    vet[7] = "PLUS";//7
    vet[8] = "MINUS";//8
    vet[9] = "MULT";//9
    vet[10] = "DIV";//10
    vet[11] = "EQ";//11
    vet[12] = "ATROP";//12
    vet[13] = "DIFF";//13
    vet[14] = "NOT";//14
    vet[15] = "SEP";//15
    vet[16] = "LPAR";//16
    vet[17] = "RPAR";//17
    vet[18] = "LCOL";//18
    vet[19] = "RCOL";//19
    vet[20] = "LCHAVE";//20
    vet[21] = "RCHAVE";//21
    vet[22] = "PONTO_VIRGULA";//22
    vet[23] = "PONTO";//23
    vet[24] = "VIRGULA";//24
    vet[25] = "PALAVRA_RESERVADA";//25
    vet[26] = "STR";//26
    vet[27] = "END_OF_FILE";//27
}

void
Parser::freeVetor()
{
    delete[] vet;
}

void
Parser::printToken(Token* t)
{
    cout << "(" << vet[t->name];

    if (t->name == END_OF_FILE)
        cout << ");";
    else if (t->attribute != UNDEF)
        cout << ", " << vet[t->attribute] << ")";
    else if (t->attribute == UNDEF)
        cout << ", " << t->lexeme << ")";

    cout << " ";
}

int 
Parser::isNumber(string num)
{
	int numType = -1;
	for (char ch : num) {
        if (isdigit(ch)) {
			numType = 0;
        }
		else if (ch == '.') {
			numType = 1;
			break;
		}
    }
	return numType;
}

void
Parser::error(string str)
{
	cout << endl << endl << str << endl;

	exit(EXIT_FAILURE);
}