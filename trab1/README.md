Instruções de Uso para Makefiles

Este repositório contém dois Makefiles, cada um adaptado para ambientes específicos: um para ambientes Windows (Make.ps1) e outro para ambientes tipo Unix (Makefile).

----------------------------------------------------------------
Ambiente Windows

Pré-requisitos

    Certifique-se de ter um compilador de C++ instalado no seu sistema Windows. 
    Se não tiver, você pode baixar e instalar o MinGW, que fornece as ferramentas necessárias, incluindo o g++.
    Certifique-se de que o diretório MinGW/bin esteja adicionado à variável de ambiente PATH do seu sistema.

Uso

    Abra o PowerShell.
    Navegue até o diretório que contém o Make.ps1.
    Digite o seguinte comando para usar o alvo padrão que compila, executa e limpa seu programa C++:
        .\Make.ps1

    Ou use o seguinte comando para usar uma alvo específica:
        .\Make.ps1 <nome_do_alvo>

Descrições dos Alvos

    .\Make.ps1 compile: Compila os arquivos fonte C++ em um executável.
    .\Make.ps1 run: Executa o executável.
    .\Make.ps1 clean: Remove o arquivo executável.
    .\Make.ps1 help: Exibe informações sobre como acessar os comandos disponíveis.
    .\Make.ps1 commands: Fornece uma lista de comandos disponíveis com descrições breves.

----------------------------------------------------------------
Ambiente tipo Unix

Pré-requisitos

    Certifique-se de ter o g++ instalado no seu sistema tipo Unix. 
    Se não tiver, você pode instalá-lo usando o seu gerenciador de pacotes.
    Certifique-se de ter o utilitário make instalado no seu sistema.

Uso

    Abra seu terminal.
    Navegue até o diretório que contém o Makefile_unix.
    Digite o seguinte comando para usar o alvo padrão que compila, executa e limpa seu programa C++:
        make
    
    Ou use o seguinte comando para usar uma alvo específica:
        make <nome_do_alvo>

Descrições dos Alvos

    make compile: Compila os arquivos fonte C++ em um executável.
    make run: Executa o executável.
    make clean: Remove o arquivo executável.
    make help: Exibe informações sobre como acessar os comandos disponíveis.
    make commands: Fornece uma lista de comandos disponíveis com descrições breves.

----------------------------------------------------------------
link para a gramática da linguagem mini java: https://dcc.ufrj.br/~fabiom/comp20151/minijava.html
