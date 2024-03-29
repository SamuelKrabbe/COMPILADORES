#include "scanner.h"    

//Construtor que recebe uma string com o nome do arquivo 
//de entrada e preenche input com seu conteúdo.
Scanner::Scanner(string input)
{
    /*this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;*/
    pos = 0;
    line = 1;

    ifstream inputFile(input, ios::in);
    string line;

    if (inputFile.is_open())
    {
        while (getline(inputFile,line) )
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else 
        cout << "Unable to open file\n"; 

    // cout << this->input << endl; 
}

int
Scanner::getLine()
{
    return line;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    Token* token;
    string lexeme = "";

    int state = 0;

    while (true)
    {
        switch(state)
        {
            case 0: // 8, 11, 26, 39
                if (input[pos] == '\0')
                {
                    token = new Token(END_OF_FILE);
                    return token;
                }
                else if (isalpha(input[pos])) 
                    state = 1;
                else if (isdigit(input[pos])) 
                    state = 9;
                else if (isspace(input[pos]))
                    state = 40;
                else if (input[pos] == '&')
                    state = 12;
                else if (input[pos] == '<')
                    state = 14;
                else if (input[pos] == '>')
                    state = 15;
                else if (input[pos] == '+')
                    state = 16;
                else if (input[pos] == '-')
                    state = 17;
                else if (input[pos] == '*')
                    state = 18;
                else if (input[pos] == '/')
                    state = 19;
                else if (input[pos] == '=')
                    state = 24;
                else if (input[pos] == '!')
                    state = 27;
                else if (input[pos] == '(')
                    state = 30;
                else if (input[pos] == ')')
                    state = 31;
                else if (input[pos] == '[')
                    state = 32;
                else if (input[pos] == ']')
                    state = 33;
                else if (input[pos] == '{')
                    state = 34;
                else if (input[pos] == '}')
                    state = 35;
                else if (input[pos] == ';')
                    state = 36;
                else if (input[pos] == '.')
                    state = 37;
                else if (input[pos] == ',')
                    state = 38;
                else if (input[pos] == '"')
                    state = 41;
                else 
                    lexicalError("Token mal formado\n");
                lexeme += input[pos];
                pos++;
                break;

            case 1:
                if (!isalpha(input[pos])) {
                    state = 3;
                    break;
                }
                lexeme += input[pos];
                pos++;
                break;  

            case 2: 
                if (!isdigit(input[pos])) {
                    state = 43;
                    break;
                }
                lexeme += input[pos];
                pos++;
                break;

            case 3:
                if (isdigit(input[pos]) || input[pos] == '_') {
                    state = 5;
                }
                else if (input[pos] == '.') {
                    state = 0;
                    lexeme += input[pos];
                    pos++;
                }
                else {
                    state = 4;
                }
                break;

            // TRATAMENTO PARA PALAVRAS RESERVADAS E ID
            case 4:
                if (isReservedWord(lexeme)) {
                    token = new Token(PALAVRA_RESERVADA, lexeme);
                }
                else if (isValidID(lexeme))
                    token = new Token(ID, lexeme);
                else
                    lexicalError("Token mal formado\n");
                return token;
                
            case 5:
                if (!isalpha(input[pos]) && !isdigit(input[pos]) && input[pos] != '_') {
                    state = 4;
                    break;
                }
                lexeme += input[pos];
                pos++;
                break;

            case 9:
                if (input[pos] == '.') {
                    state = 11;
                }
                else if (!isdigit(input[pos])) {
                    state = 10;
                    break;
                }
                lexeme += input[pos];
                pos++;
                break; 

            case 10: // INTEGER_LITERAL
                token = new Token(INTEGER_LITERAL, lexeme);
                return token;

            case 11:
                if (isdigit(input[pos])) {
                    state = 2;
                }
                else
                    lexicalError("Token mal formado\n");
                lexeme += input[pos];
                pos++;
                break;

            case 12:
                if (input[pos] == '&')
                    state = 13;
                else 
                    lexicalError("Token mal formado\n");
                lexeme = input[pos];
                pos++;
                break;

            case 13: // AND
                token = new Token(OP, AND);
                return token;

            case 14: // LT
                token = new Token(OP, LT);
                return token;

            case 15: // GT
                token = new Token(OP, GT);
                return token;

            case 16: // PLUS
                token = new Token(OP, PLUS);
                return token;

            case 17: // MINUS
                token = new Token(OP, MINUS);
                return token;

            case 18: // MULT
                token = new Token(OP, MULT);
                return token;

            case 19:
                if (input[pos] == '/') {
                    state = 21;
                }
                else if (input[pos] == '*'){
                    state = 22;
                }
                else {
                    state = 20;
                    break;
                }
                lexeme += input[pos];
                pos++;
                break; 
            
            case 20: // DIV
                token = new Token(OP, DIV);
                return token;

            case 21: // COMENTÁRIO EM LINHA
                if (input[pos] == '\n') {
                    state = 0;
                    lexeme = "";
                    pos++;
                    break;
                }
                lexeme += input[pos];
                pos++;
                break; 
            
            case 22: // COMENTÁRIO EM BLOCO
                if (input[pos] == '*') {
                    pos++;
                    if (input[pos] == '/') {
                        state = 0;
                        lexeme = "";
                        pos++;
                        break; 
                    }
                }
                lexeme += input[pos];
                pos++;
                break;

            case 24:
                if (input[pos] != '=') {
                    state = 25;
                    lexeme += input[pos];
                    break;
                }
                state = 26;
                lexeme += input[pos];
                pos++;
                break; 

            case 25: // EQ
                token = new Token(OP, EQ);
                return token;

            case 26: // ATROP
                token = new Token(OP, ATROP);
                return token;

            case 27:
                if (input[pos] != '=') {
                    state = 28;
                    lexeme += input[pos];
                    break;
                }
                state = 29;
                lexeme += input[pos];
                pos++;
                break; 

            case 28: // DIFF
                token = new Token(OP, DIFF);
                return token;

            case 29: // NOT
                token = new Token(OP, NOT);
                return token;

            case 30: // LPAR
                token = new Token(SEP, LPAR);
                return token;

            case 31: // RPAR
                token = new Token(SEP, RPAR);
                return token;

            case 32: // LCOL
                token = new Token(SEP, LCOL);
                return token;

            case 33: // RCOL
                token = new Token(SEP, RCOL);
                return token;

            case 34: // LCHA
                token = new Token(SEP, LCHAVE);
                return token;

            case 35: // RCHA
                token = new Token(SEP, RCHAVE);
                return token;

            case 36: // PONTO_VIRGULA
                token = new Token(SEP, PONTO_VIRGULA);
                return token;

            case 37: // PONTO
                token = new Token(SEP, PONTO);
                return token;

            case 38: // VIRGULA
                token = new Token(SEP, VIRGULA);
                return token;

            case 40: // TRATAMENTO PARA ESPAÇOS EM BRANCO
                if (!isspace(input[pos])) {
                    state = 0;
                    lexeme = "";
                    break;
                }
                pos++;
                break;

            case 41:
                if (input[pos] == '"') {
                    state = 42;
                }
                lexeme += input[pos];
                pos++;
                break;

            case 42: // STR
                token = new Token(STR, lexeme);
                return token;

            case 43: // FLOAT_LITERAL
                token = new Token(FLOAT_LITERAL, lexeme);
                return token;

            default:
                lexicalError("Token mal formado\n");

        }
    }

    return token;
 
}

//Método que verifica se um lexema é uma palavra reservada
bool 
Scanner::isReservedWord(string lexeme){
    int arrayLength = sizeof(reserved_words) / sizeof(reserved_words[0]);

    for (int i = 0; i < arrayLength; ++i) {
        if (reserved_words[i] == lexeme)
            return true;
    }
    return false;
}

//Método para validar um ID
bool 
Scanner::isValidID(string id){
    for (char ch : id) {
        if (ch == '.') {
            return false; // ID é inválido se contém um ponto
        }
    }
    return true;
}

void 
Scanner::lexicalError(string msg)
{
    cout << "Linha "<< line << ": " << msg << endl;
    
    exit(EXIT_FAILURE);
}
