/* Author(s): Samuel de Oliveira Krabbe
 * Analizador Léxico
*/

#include <iostream>
#include "parser.h"
// #include "scanner.h"

using namespace std;

// string* vet;

// void print(Token*);
// void allocVetor();
// void freeVetor();

int main(int argc, char* argv[]) 
{
    //Verifica se foi executado corretamente
    //Essa main espera receber o nome do arquivo a ser
    //executado na linha de comando.
    if (argc != 2)
    {
        cout << "Uso: ./compiler nome_arquivo.mj\n";
        return 1;
    }
    
    Parser* parser = new Parser(argv[1]);
    parser->run();
    delete parser;

    //getline(cin, input);

    // Scanner* scanner = new Scanner(argv[1]);
    
    // allocVetor();

    // Token* t;
    // do
    // {
    //     t = scanner->nextToken();
        
    //     // cout << t->name << " ";
    //     print(t);
    // }while (t->name != END_OF_FILE);

    // delete scanner;

    // freeVetor();
    
    return 0;
}

// void allocVetor()
// {
//     vet = new string[29];

//     vet[0] = "UNDEF";//0
//     vet[1] = "ID";//1
//     vet[2] = "INTEGER_LITERAL";//2
//     vet[3] = "OP";//3
//     vet[4] = "AND";//4
//     vet[5] = "LT";//5
//     vet[6] = "GT";//6
//     vet[7] = "PLUS";//7
//     vet[8] = "MINUS";//8
//     vet[9] = "MULT";//9
//     vet[10] = "DIV";//10
//     vet[11] = "EQ";//11
//     vet[12] = "ATROP";//12
//     vet[13] = "DIFF";//13
//     vet[14] = "NOT";//14
//     vet[15] = "SEP";//15
//     vet[16] = "LPAR";//16
//     vet[17] = "RPAR";//17
//     vet[18] = "LCOL";//18
//     vet[19] = "RCOL";//19
//     vet[20] = "LCHAVE";//20
//     vet[21] = "RCHAVE";//21
//     vet[22] = "PONTO_VIRGULA";//22
//     vet[23] = "PONTO";//23
//     vet[24] = "VIRGULA";//24
//     vet[25] = "PALAVRA_RESERVADA";//25
//     vet[26] = "STR";//26
//     vet[27] = "FLOAT_LITERAL", //27
//     vet[28] = "END_OF_FILE";//28
// }

// void freeVetor()
// {
//     delete[] vet;
// }

// void print(Token* t)
// {
//     cout << "(" << vet[t->name];

//     if (t->name == END_OF_FILE)
//         cout << ");";
//     else if (t->attribute != UNDEF)
//         cout << ", " << vet[t->attribute] << ")";
//     else if (t->attribute == UNDEF)
//         cout << ", " << t->lexeme << ")";

//     cout << " ";
// }