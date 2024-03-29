#include <fstream>
#include "token.h"

class Scanner 
{
    private: 
        string input;//Armazena o texto de entrada
        int pos;//Posição atual
        int line;
        string reserved_words[19] = 
        {
        "boolean", 
        "class", 
        "extends", 
        "public", 
        "static", 
        "void", 
        "main", 
        "String", 
        "return", 
        "int", 
        "if", 
        "else", 
        "while", 
        "System.out.println", 
        "length", 
        "true", 
        "false", 
        "this", 
        "new"
    };
    
    public:
    //Construtor
        Scanner(string);

        int getLine();

        //Método que retorna o próximo token da entrada
        Token* nextToken();   

        //Método que verifica se um lexema é uma palavra reservada
        bool isReservedWord(string);

        //Método para validar um ID
        bool isValidID(string id);
    
        //Método para manipular erros
        void lexicalError(string);
};
