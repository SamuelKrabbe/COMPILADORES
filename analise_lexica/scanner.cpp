#include "scanner.h"    

//Construtor
Scanner::Scanner(string input)
{
    this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;
    pos = 0;
}

//Método que retorna o próximo token da entrada
Token* 
Scanner::nextToken()
{
    
    Token* token;
    int state = 0;

    while (true)
    {
        switch(state)
        {
            case 0:
                if (input[pos] == '\0')
                {
                    token = new Token(END_OF_FILE);
                    return token;
                }
                else if (isdigit(input[pos])) 
                    state = 1;
                else if (isalpha(input[pos])) 
                    state = 19;
                else if (isspace(input[pos])) 
                    state = 30;
                else if (input[pos] == '=')
                    state = 17;
                else if (input[pos] == '+')
                    state = 9;
                else if (input[pos] == '-')
                    state = 11;
                else if (input[pos] == '/')
                    state = 13;
                else if (input[pos] == '*')
                    state = 15;
                else if (input[pos] == '(')
                    state = 21;
                else if (input[pos] == ')')
                    state = 23;
                else if (input[pos] == '[')
                    state = 25;
                else if (input[pos] == ']')
                    state = 27;
                else 
                    lexicalError();
                    
                pos++;
                break;

            case 1:
                if (isdigit(input[pos])) 
                    state = 1;
                else if (input[pos] == '.') 
                    state = 3;
                else if (input[pos] == 'E') 
                    state = 5;
                else
                    state = 2;
                pos++;
                break;

            case 2:
                token = new Token(INTEGER_LITERAL);
                pos--;
                return token;

            case 3:
                if (isdigit(input[pos])) 
                    state = 4;
                else 
                    lexicalError();
                pos++;
                break;

            case 4:
                if (isdigit(input[pos])) 
                    state = 4;
                else if (input[pos] == 'E') 
                    state = 5;
                else
                    state = 29;
                pos++;
                break;

            case 5:
                if (input[pos] == '+' || input[pos] == '-') 
                    state = 6;
                else if (isdigit(input[pos])) 
                    state = 7;
                pos++;
                break;

            case 6:
                if (isdigit(input[pos])) 
                    state = 7;
                pos++;
                break;

            case 7:
                if (!isdigit(input[pos])) 
                    state = 8;
                pos++;
                break;

            case 8:
                token = new Token(DOUBLE_LITERAL);
                pos--;
                return token;

            case 9:
                state = 10;
                pos++;
                break;

            case 10:
                token = new Token(RELOP, PLUS);
                pos--;
                return token;

            case 11:
                state = 12;
                pos++;
                break;

            case 12:
                token = new Token(RELOP, MINUS);
                pos--;
                return token;

            case 13:
                state = 14;
                pos++;
                break;

            case 14:
                token = new Token(RELOP, DIV);
                pos--;
                return token;

            case 15:
                state = 16;
                pos++;
                break;

            case 16:
                token = new Token(RELOP, MULT);
                pos--;
                return token;

            case 17:
                state = 18;
                pos++;
                break;

            case 18:
                token = new Token(ATROP);
                pos--;
                return token;

            case 19:
                if (!isalpha(input[pos])) 
                    state = 20;
                pos++;
                break;

            case 20:
                token = new Token(ID);
                pos--;
                return token;

            case 21:
                state = 22;
                pos++;
                break;

            case 22:
                token = new Token(SEP, LPAR);
                pos--;
                return token;

            case 23:
                state = 24;
                pos++;
                break;

            case 24:
                token = new Token(SEP, RPAR);
                pos--;
                return token;

            case 25:
                state = 26;
                pos++;
                break;

            case 26:
                token = new Token(SEP, LBRA);
                pos--;
                return token;

            case 27:
                state = 28;
                pos++;
                break;

            case 28:
                token = new Token(SEP, RBRA);
                pos--;
                return token;

            case 29:
                token = new Token(FLOAT_LITERAL);
                pos--;
                return token;

            case 30:
                if (!isspace(input[pos])) 
                    state = 0;
                break;

            default:
                lexicalError();

        }
    }
}//Fim nextToken

void 
Scanner::lexicalError()
{
    cout << "Token mal formado\n";
    
    exit(EXIT_FAILURE);
}
