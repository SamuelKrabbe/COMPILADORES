// PROG   -> MAIN {CLASSE}
// MAIN   -> class id '{' public static void main ( String [ ] id ) '{' CMD '}' '}'
// CLASSE -> class id [extends id] '{' {VAR} {METODO} '}'
// VAR    -> TIPO id ;
// METODO -> public TIPO id '(' [PARAMS] ')' '{' {VAR} {CMD} return EXP ; '}'
// PARAMS -> TIPO id {, TIPO id}
// TIPO   -> int INT_
//         | boolean
//         | id
// INT_   -> '[' ']'
//         | epsilon
// CMD    -> '{' {CMD} '}'
//         | if '(' EXP ')' CMD ELSE_
//         | while '(' EXP ')' CMD
//         | System.out.println '(' EXP ')' ;
//         | id ID_
// ELSE_   -> else CMD
//         | epsilon
// ID_   -> = EXP ;
//         | '[' EXP ']' = EXP ;
// EXP    -> REXP EXP_
// EXP_   -> && REXP EXP_
//         | epsilon
// REXP   -> AEXP REXP_
// REXP_   -> < AEXP REXP_
//         | == AEXP REXP_
//         | != AEXP REXP_
//         | epsilon
// AEXP   -> MEXP AEXP_
// AEXP_   -> + MEXP AEXP_
//         | - MEXP AEXP_
//         | epsilon
// MEXP   -> SEXP MEXP_
// MEXP_   -> * SEXP MEXP_
//         | / SEXP MEXP_
//         | epsilon
// SEXP   -> ! SEXP
//         | - SEXP
//         | true
//         | false
//         | num (INTEGER_LITERAL || FLOAT_LITERAL)
//         | new SEXP_NEW
// SEXP_NEW-> int '[' EXP ']'
//         | PEXP SEXP_
// SEXP_   -> . length
//         | '[' EXP ']'
//         | epsilon
// PEXP   -> id PEXP_
//         | this PEXP_
//         | new id '(' ')' PEXP_
//         | '(' EXP ')' PEXP_
// PEXP_   -> . id PEXP_PID
//         | epsilon
// PEXP_PID-> PEXP_
//         | '(' [EXPS] ')' PEXP_
// EXPS   -> EXP {, EXP}

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
        void params();
        void tipo();
        void int_();
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
        void sexp_aux();
        void sexp_();
        void pexp();
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
