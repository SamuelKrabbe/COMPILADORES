Instruções de Uso para Makefiles
----------------------------------------------------------------

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
