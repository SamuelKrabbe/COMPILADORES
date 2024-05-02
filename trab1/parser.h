#include "scanner.h"

class Parser
{
    private:
        Scanner* scanner;
        Token* lookahead;
        string* vet;

        void advance();
        void match(int, string);

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
        void rexp();
        void rexp_();
        void aexp();
        void aexp_();
        void mexp();
        void mexp_();
        void sexp();
        void sexp_();
        void pexp();
        void new_();
        void pexp_();
        void pexp_pid();
        void exps();

        void printToken(Token*);
        void allocVetor();
        void freeVetor();
        int isNumber(string);
        void error(string);
        
    public:
        Parser(string);
        void run();
};
