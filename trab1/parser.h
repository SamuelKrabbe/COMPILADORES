// PROG   -> MAIN {CLASSE}
// MAIN   -> class id '{' public static void main ( String [ ] id ) '{' CMD '}' '}'
// CLASSE -> class id [extends id] '{' {VAR} {METODO} '}'
// VAR    -> TIPO id ;
// METODO -> public TIPO id '(' [PARAMS] ')' '{' {VAR} {CMD} return EXP ; '}'
// PARAMS -> TIPO id {, TIPO id}
// TIPO   -> int '[' ']'
//         | boolean
//         | int
//         | id
// CMD    -> '{' {CMD} '}'
//         | if '(' EXP ')' CMD
//         | if '(' EXP ')' CMD else CMD
//         | while '(' EXP ')' CMD
//         | System.out.println '(' EXP ')' ;
//         | id = EXP ;
//         | id '[' EXP ']' = EXP ;
// EXP    -> EXP && REXP
//         | REXP
// REXP   -> REXP < AEXP
//         | REXP == AEXP
//         | REXP != AEXP
//         | AEXP
// AEXP   -> AEXP + MEXP
//         | AEXP - MEXP
//         | MEXP
// MEXP   -> MEXP * SEXP
//         | MEXP / SEXP
//         | SEXP
// SEXP   -> ! SEXP
//         | - SEXP
//         | true
//         | false
//         | num
//         | new int '[' EXP ']'
//         | PEXP . length
//         | PEXP '[' EXP ']'
//         | PEXP
// PEXP   -> id
//         | this
//         | new id '(' ')'
//         | '(' EXP ')'
//         | PEXP . id
//         | PEXP . id '(' [EXPS] ')'
// EXPS   -> EXP {, EXP}

#include "scanner.h"

class Parser
{
    private:
        Scanner* scanner;
        Token* lookahead;

        void advance();
        void match(int, string);

        void prog();
        void main();
        void classe();
        void var();
        void metodo();
        void params();
        void tipo();
        void cmd();
        void exp();
        void rexp();
        void aexp();
        void mexp();
        void sexp();
        void pexp();
        void exps();

        void error(string);
        
    public:
        Parser(string);

        void run();
};
