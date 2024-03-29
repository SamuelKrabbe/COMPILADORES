#include "scanner.h"

string* vet;

void print(Token*);
void allocVetor();
void freeVetor();

int main(/*int argc, char* argv[]*/) 
{
    string input;
    
    getline(cin, input);

    Scanner* scanner = new Scanner(input);

    allocVetor();
    
    Token* t;
    
    do
    {
        t = scanner->nextToken();
        //cout << t->name << " ";
        print(t);
    }while (t->name != END_OF_FILE);

    delete scanner;

    freeVetor();

    return 0;
}

void allocVetor()
{
    vet = new string[17];

    vet[0] = "UNDEF";//0
    vet[1] = "ID";//1
    vet[2] = "RELOP";//2
    vet[3] = "ATROP";//3
    vet[4] = "PLUS";//4
    vet[5] = "MINUS";//5
    vet[6] = "DIV";//6
    vet[7] = "MULT";//7
    vet[8] = "SEP";//8
    vet[9] = "LPAR";//9
    vet[10] = "RPAR";//10
    vet[11] = "LBRA";//11
    vet[12] = "RBRA";//12
    vet[13] = "DOUBLE_LITERAL";//13
    vet[14] = "FLOAT_LITERAL";//14
    vet[15] = "INTEGER_LITERAL";//15
    vet[16] = "END_OF_FILE";//16
}

void freeVetor()
{
    delete[] vet;
}

void print(Token* t)
{
    cout << vet[t->name];

    if (t->attribute != UNDEF)
        cout << "(" << vet[t->attribute] << ")";

    cout << " ";
}