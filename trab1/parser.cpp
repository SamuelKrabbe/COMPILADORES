#include "parser.h"
#include <string>

bool isMainClass = false;

Parser::Parser(string input)
{
	globalST = new SymbolTable();
	currentST = new SymbolTable(globalST);
	initSimbolTable();
	scanner = new Scanner(input);
	allocVetor();
    advance();
}

void
Parser::run()
{
    prog();
	freeVetor();
	cout << "Compilação encerrada com sucesso" << endl;
}

void
Parser::advance()
{
	lookahead = scanner->nextToken();
	// printToken(lookahead);
    // cout << lookahead->lexeme << " ";
}

void
Parser::match(int t, string keyword = "")
{
	if (lookahead->name == t || lookahead->attribute == t || lookahead->lexeme.compare(keyword) == 0) {
		advance();
	}
	else {
		string expectedToken;
        if (t != -1) {
            expectedToken = "Expected token " + vet[t];
        }
        else {
            expectedToken = "Expected keyword \"" + keyword + "\"";
        }
        error(expectedToken + " but found \"" + lookahead->lexeme + "\"", scanner->getLine());
    }
}

// PROG   -> MAIN {CLASSE}
void 
Parser::prog()
{
	// cout << "prog" << " ";
	newScope();
	main();
	while (lookahead->lexeme.compare("class") == 0)
		classe();
	clearScope();
}

// MAIN   -> class id '{' public static void main '(' String '[' ']' id ')' '{' CMD '}' '}'
void 
Parser::main()
{
	// cout << "main" << " ";
	isMainClass = true;
	match(-1, "class");
	currentST->add(new STEntry(new Token(ID, lookahead->lexeme)));
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
	isMainClass = false;
}

// CLASSE -> class id [extends id] '{' {VAR} {METODO} '}'
void 
Parser::classe()
{
	// cout << "classe" << " ";
	newScope();
	match(-1, "class");
	currentST->add(new STEntry(new Token(ID, lookahead->lexeme)));
	match(ID);
	if (lookahead->lexeme.compare("extends") == 0) {
		match(-1, "extends");
		if (currentST->get(lookahead->lexeme)) {
			match(ID);
		} else {
			error("'" + lookahead->lexeme + "' not declared", scanner->getLine());
		}
	}
	match(LCHAVE);
	if (lookahead->lexeme.compare("'}'") != 0) {
		while (lookahead->lexeme.compare("int") == 0 || lookahead->lexeme.compare("boolean") == 0 || lookahead->name == ID) {
            var();
        }
		while (lookahead->lexeme.compare("public") == 0) {
            metodo();
        }
	}
	match(RCHAVE);
	clearScope();
}

// VAR    -> TIPO id ;
void 
Parser::var()
{
	// cout << "var" << " ";
	tipo();
	currentST->add(new STEntry(new Token(ID, lookahead->lexeme)));
	match(ID);
	match(PONTO_VIRGULA);
}

// METODO -> public TIPO id '(' [PARAMS] ')' '{' {VAR} {CMD} return EXP ; '}'
void 
Parser::metodo()
{
	// cout << "metodo" << " ";
	newScope();
	match(-1, "public");
	tipo();
	currentST->add(new STEntry(new Token(ID, lookahead->lexeme)));
	match(ID);
	match(LPAR);
	if (lookahead->lexeme.compare("')'") != 0) {
		if (lookahead->lexeme.compare("int") == 0 || lookahead->lexeme.compare("boolean") == 0 || lookahead->name == ID) {
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
		while (lookahead->name == ID) {
			id();
		}
		if (lookahead->lexeme.compare("return") == 0) {
			match(-1, "return");
			exp();
			match(PONTO_VIRGULA);
		}
	}
	match(RCHAVE);
	clearScope();
}

void 
Parser::id()
{
	// cout << "id" << " ";
	if (currentST->get(lookahead->lexeme)) {
		match(ID);
		if (lookahead->lexeme.compare("=") == 0 || lookahead->lexeme.compare("'['") == 0) {
			id_();
		} else {
			string expectedToken;
			expectedToken = "Expected keyword \"=\" or \"[\"";
			error(expectedToken + " but found \"" + lookahead->lexeme + "\"", scanner->getLine());
		}
	} else {
		error("Error: \"" + lookahead->lexeme + "\" not declared", scanner->getLine());
	}
}

// PARAMS -> TIPO id {, TIPO id}
void 
Parser::params()
{
	// cout << "params" << " ";
	tipo();
	currentST->add(new STEntry(new Token(ID, lookahead->lexeme)));
	match(ID);
	while (lookahead->lexeme.compare("','") == 0) {
		match(VIRGULA);
		tipo();
		currentST->add(new STEntry(new Token(ID, lookahead->lexeme)));
		match(ID);
	}
	
}

// TIPO   -> int ([])?
//         | boolean
//         | id
void 
Parser::tipo()
{
	// cout << "tipo" << " ";
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
	else if (lookahead->name == ID) {
		currentST->add(new STEntry(new Token(ID, lookahead->lexeme), true));
		match(ID);
	} else {
		error("TypeError: Invalid type", scanner->getLine());
	}
}

// CMD    -> '{' {CMD} '}'
//         | if '(' EXP ')' CMD ELSE_
//         | while '(' EXP ')' CMD
//         | System.out.println '(' EXP ')' ;
//         | id ID_
void 
Parser::cmd()
{
	newScope();
	// cout << "cmd" << " ";
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
	else if (lookahead->name == ID) {
		if (isMainClass) {
			match(ID);
        	id_();
		} else {
			if(currentST->get(lookahead->lexeme)) {
				match(ID);
        		id_();
			} else {
				error("'" + lookahead->lexeme + "' not declared", scanner->getLine());
			}
		}
    }
    else {
        error("Invalid token", scanner->getLine());
    }
	clearScope();
	
}

// ELSE_   -> else CMD
//         | epsilon
void 
Parser::else_()
{
	// cout << "else_" << " ";
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
	// cout << "id_" << " ";
	if (lookahead->lexeme.compare("'['") == 0) {
		match(-1, "'['");
		exp();
		match(-1, "']'");
	}
	match(ATROP);
	exp();
	match(PONTO_VIRGULA);
}

// EXP    -> relexp EXP_
void 
Parser::exp()
{
	// cout << "exp" << " ";
	relexp();
	exp_();
}

// EXP_   -> && relexp EXP_
//         | epsilon
void 
Parser::exp_()
{
	// cout << "exp_" << " ";
	if (lookahead->lexeme.compare("&&") == 0) {
		relexp();
		exp_();
	}
}

// relexp   -> addexp relexp_
void 
Parser::relexp()
{
	// cout << "relexp" << " ";
	addexp();
	relexp_();
}

// relexp_   -> < addexp relexp_
//         | == addexp relexp_
//         | != addexp relexp_
//         | epsilon
void 
Parser::relexp_()
{
	// cout << "relexp_" << " ";
	if (lookahead->lexeme.compare("<") == 0) {
        match(LT);
		addexp();
		relexp_();
    }
	else if (lookahead->lexeme.compare("==") == 0) {
        match(EQ);
		addexp();
		relexp_();
    }
	else if (lookahead->lexeme.compare("!=") == 0) {
        match(DIFF);
		addexp();
		relexp_();
    }
	
}

// addexp   -> multexp addexp_
void 
Parser::addexp()
{
	// cout << "addexp" << " ";
	multexp();
	addexp_();
}

// addexp_   -> + multexp addexp_
//         | - multexp addexp_
//         | epsilon
void 
Parser::addexp_()
{
	// cout << "addexp_" << " ";
	if (lookahead->lexeme.compare("+") == 0) {
        match(PLUS);
		multexp();
		addexp_();
    }
	else if (lookahead->lexeme.compare("-") == 0) {
        match(MINUS);
		multexp();
		addexp_();
    }
}

// multexp   -> unexp multexp_
void 
Parser::multexp()
{
	// cout << "multexp" << " ";
	unexp();
	multexp_();
}

// multexp_   -> * unexp multexp_
//         | / unexp multexp_
//         | epsilon
void 
Parser::multexp_()
{
	// cout << "multexp_" << " ";
	if (lookahead->lexeme.compare("*") == 0) {
        match(MULT);
		unexp();
		multexp_();
    }
	else if (lookahead->lexeme.compare("/") == 0) {
        match(DIV);
		unexp();
		multexp_();
    }
	
}

// unexp   -> ! unexp
//         | - unexp
//         | true
//         | false
//         | INT
//		   | primexp unexp_
void 
Parser::unexp()
{
	// cout << "unexp" << " ";
	if (lookahead->lexeme.compare("!") == 0) {
        match(NOT);
        unexp();
    }
    else if (lookahead->lexeme.compare("-") == 0) {
        match(MINUS);
        unexp();
    }
    else if (lookahead->lexeme.compare("true") == 0 || lookahead->lexeme.compare("false") == 0) {
        match(-1, lookahead->lexeme); // Consome "true", "false"
    }
	else if (isNumber(lookahead->lexeme) == 0) {
        match(INT);
    }
    else if (lookahead->lexeme.compare("new") == 0) {
        primexp();
        unexp_();
    }
	else {
		error("Invalid expression", scanner->getLine());
	}
}

// unexp_   -> . length
//         | '[' EXP ']'
//         | epsilon
void 
Parser::unexp_()
{
	// cout << "unexp_" << " ";
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

// primexp   -> id primexp_
//         | this primexp_
//         | new NEW_
//         | '(' EXP ')' primexp_
void 
Parser::primexp()
{
	// cout << "primexp" << " ";
    if (lookahead->lexeme.compare("this") == 0) {
        match(-1, "this");
		primexp_();
    }
    else if (lookahead->lexeme.compare("new") == 0) {
        match(-1, "new");
        new_();
    }
    else if (lookahead->lexeme.compare("'('") == 0) {
        match(LPAR);
        exp();
        match(RPAR);
		primexp_();
    }
	else if (lookahead->name == ID) {
        match(ID);
		primexp_();
    }
	else {
		error("Invalid expression", scanner->getLine());
	}
	
}

//NEW_ -> id '(' ')'
//     | int '[' EXP ']'
void 
Parser::new_()
{
	// cout << "new_" << " ";
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
		error("Erro inesperado", scanner->getLine());
	}
	
}

// primexp_   -> . id primexp_PID
//         | epsilon
void 
Parser::primexp_()
{
	// cout << "primexp_" << " ";
	if (lookahead->lexeme.compare("'.'") == 0) {
		match(PONTO);
		match(ID);
        primexp_pid();
    }
}

// primexp_PID-> '(' [expsList] ')'
//         | epsilon
void 
Parser::primexp_pid()
{
	// cout << "primexp_pid" << " ";
    if (lookahead->lexeme.compare("'('") == 0) {
        match(LPAR);
        if (lookahead->lexeme.compare("')'") != 0) {
            expsList();
        }
        match(RPAR);
    }
}

// expsList   -> EXP {, EXP}
void 
Parser::expsList()
{
	// cout << "expsList" << " ";
	exp();
	while (lookahead->lexeme.compare("','") == 0) {
		match(VIRGULA);
		exp();
	}
}

void Parser::initSimbolTable()
{
    Token* t;

    t = new Token(CLASS, "class");
    globalST->add(new STEntry(t, true));
    t = new Token(EXTENDS, "extends");
    globalST->add(new STEntry(t, true));
    t = new Token(PUBLIC, "public");
    globalST->add(new STEntry(t, true));
    t = new Token(STATIC, "static");
    globalST->add(new STEntry(t, true));
    t = new Token(VOID, "void");
    globalST->add(new STEntry(t, true));
    t = new Token(MAIN, "main");
    globalST->add(new STEntry(t, true));
    t = new Token(STRING, "String");
    globalST->add(new STEntry(t, true));
    t = new Token(RETURN, "return");
    globalST->add(new STEntry(t, true));
    t = new Token(INT, "int");
    globalST->add(new STEntry(t, true));
    t = new Token(IF, "if");
    globalST->add(new STEntry(t, true));
    t = new Token(ELSE, "else");
    globalST->add(new STEntry(t, true));
    t = new Token(WHILE, "while");
    globalST->add(new STEntry(t, true));
    t = new Token(SYSTEM_OUT_PRINTLN, "System.out.println");
    globalST->add(new STEntry(t, true));
    t = new Token(LENGTH, "length");
    globalST->add(new STEntry(t, true));
    t = new Token(TRUE, "true");
    globalST->add(new STEntry(t, true));
    t = new Token(FALSE, "false");
    globalST->add(new STEntry(t, true));
    t = new Token(THIS, "this");
    globalST->add(new STEntry(t, true));
    t = new Token(NEW, "new");
    globalST->add(new STEntry(t, true));
}

void Parser::allocVetor()
{
    vet = new std::string[48]; 

    vet[1] = "UNDEF";
	vet[2] = "ID";
	vet[3] = "OP";
	vet[4] = "AND";
	vet[5] = "LT";
	vet[6] = "GT";
	vet[7] = "PLUS";
	vet[8] = "MINUS";
	vet[9] = "MULT";
	vet[10] = "DIV";
	vet[11] = "EQ";
	vet[12] = "ATROP"; 
	vet[13] = "DIFF"; 
	vet[14] = "NOT"; 
	vet[15] = "SEP";
	vet[16] = "LPAR";
	vet[17] = "RPAR";
	vet[18] = "LCOL"; 
	vet[19] = "RCOL"; 
	vet[20] = "LCHAVE"; 
	vet[21] = "RCHAVE"; 
	vet[22] = "PONTO_VIRGULA";
	vet[23] = "PONTO"; 
	vet[24] = "VIRGULA"; 
	vet[25] = "PALAVRA_RESERVADA"; 
	vet[26] = "END_OF_FILE"; 


    // Adicione as novas palavras reservadas
    vet[28] = "BOOLEAN"; //28
    vet[29] = "CLASS"; //29
    vet[30] = "EXTENDS"; //30
    vet[31] = "PUBLIC"; //31
    vet[32] = "STATIC"; //32
    vet[33] = "VOID"; //33
    vet[34] = "MAIN"; //34
    vet[35] = "STRING"; //35
    vet[36] = "RETURN"; //36
    vet[37] = "INT"; //37
    vet[38] = "IF"; //38
    vet[39] = "ELSE"; //39
    vet[40] = "WHILE"; //40
    vet[41] = "SYSTEM_OUT_PRINTLN"; //41
    vet[42] = "LENGTH"; //42
    vet[43] = "TRUE"; //43
    vet[44] = "FALSE"; //44
    vet[45] = "THIS"; //45
    vet[46] = "NEW"; //46
    vet[47] = "PALAVRA_RESERVADA"; //47
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
Parser::error(string str, int lineNumber = -1)
{
	if (lineNumber != -1) {
        cout << "Linha:" << lineNumber << ": ";
    }
	cout << str << endl;

	exit(EXIT_FAILURE);
}

void
Parser::newScope()
{
	SymbolTable* newScope = new SymbolTable(currentST);
	currentST = newScope;
}

void
Parser::clearScope()
{
	SymbolTable* aux;
	aux = currentST->getParent();
	currentST->clear();
	currentST = aux;
}
