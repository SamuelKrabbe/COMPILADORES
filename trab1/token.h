#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,
    ID,
    OP,
    AND, // &&
    LT, // <
    GT, // >
    PLUS, // +
    MINUS, // -
    MULT, // *
    DIV, // /
    EQ, // ==
    ATROP, // =
    DIFF, // !=
    NOT, // !
    SEP,
    LPAR, // (
    RPAR, // )
    LCOL, // [
    RCOL, // ]
    LCHAVE, // {
    RCHAVE, // }
    PONTO_VIRGULA, // ;
    PONTO, // .
    VIRGULA, // ,
    PALAVRA_RESERVADA,
    END_OF_FILE,

    // Palavras Reservadas em MiniJava modificada
    BOOLEAN,
    CLASS,
    EXTENDS,
    PUBLIC,
    STATIC,
    VOID,
    MAIN,
    STRING,
    RETURN,
    INT,
    IF,
    ELSE,
    WHILE,
    SYSTEM_OUT_PRINTLN,
    LENGTH,
    TRUE,
    FALSE,
    THIS,
    NEW
};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name)
        {
            this->name = name;
            this->attribute = UNDEF;
            this->lexeme = "";
        }

        Token(int name, string lexeme)
        {
            this->name = name;
            this->attribute = UNDEF;
            this->lexeme = lexeme;
        }
        
        Token(int name, int attribute)
        {
            this->name = name;
            this->attribute = attribute;
            this->lexeme = "";
        }
};
