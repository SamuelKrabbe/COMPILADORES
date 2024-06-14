/* Author(s): Samuel de Oliveira Krabbe, Yan Marcos, Lucas Arruda
 * Compilador de MiniJava
*/

#include <iostream>
#include "parser.h"

using namespace std;

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
    
    return 0;
}
