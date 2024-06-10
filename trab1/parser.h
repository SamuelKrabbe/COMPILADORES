#include "scanner.h"

class Parser
{
    private:
        Scanner* scanner;
        Token* lookahead;
        string* vet;
        SymbolTable* globalST;
    	SymbolTable* currentST;

        void advance();
        void match(int, string);
        void initSimbolTable();
        void printToken(Token*);
        void allocVetor();
        void freeVetor();
        int isNumber(string);
        void error(string, int);
        void newScope();
        void clearScope();

        void prog();
        void main();
        void classe();
        void var();
        void metodo();
        void id();
        void params();
        void tipo();
        void cmd();
        void else_();
        void id_();
        void exp();
        void exp_();
        void relexp();
        void relexp_();
        void addexp();
        void addexp_();
        void multexp();
        void multexp_();
        void unexp();
        void unexp_();
        void primexp();
        void new_();
        void primexp_();
        void primexp_pid();
        void expsList();
        
    public:
        Parser(string);
        void run();
};
