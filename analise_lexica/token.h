#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,//0
    ID,//1
    RELOP,//2
    ATROP,//3
    PLUS,//4
    MINUS,//5
    DIV,//6
    MULT,//7
    SEP,//8
    LPAR,//9
    RPAR,//10
    LBRA,//11
    RBRA,//12
    DOUBLE_LITERAL,//13
    FLOAT_LITERAL,//14
    INTEGER_LITERAL,//15
    END_OF_FILE//16
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
            attribute = UNDEF;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};