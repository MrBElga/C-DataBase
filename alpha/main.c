#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "tad.h"


// Função para remover quebra de linha de uma string
void removerQuebraDeLinha(char *str) {
    size_t length = strlen(str);
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}

// Função para executar um comando SQL
void executarComandoSQL(pontBD **banco, const char *comando) {
    char comandoCopy[1024];
    strcpy(comandoCopy, comando);

    char *token = strtok(comandoCopy, " ");
    if (token == NULL) {
        printf("Comando SQL não reconhecido: %s\n", comando);
        return;
    }

    if (strcmp(token, "CREATE") == 0) {
      
        printf("Executando CREATE TABLE...\n");
    } else if (strcmp(token, "INSERT") == 0) {
 
        printf("Executando INSERT INTO...\n");
    } else if (strcmp(token, "UPDATE") == 0) {
       
        printf("Executando UPDATE...\n");
    } else if (strcmp(token, "DELETE") == 0) {
        
        printf("Executando DELETE FROM...\n");
    } else if (strcmp(token, "SELECT") == 0) {
        
        printf("Executando SELECT...\n");
    } else if (strcmp(token, "SAIR") == 0) {
        printf("Encerrando o programa...\n");
    } else {
        printf("Comando SQL não reconhecido: %s\n", comando);
    }
}

void carregarScriptDeCriacao(pontBD **banco, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return;
    }

    char linha[1024];
    while (fgets(linha, sizeof(linha), arquivo)) {
      
        linha[strcspn(linha, "\n")] = '\0';

       
        executarComandoSQL(banco, linha);
    }

    fclose(arquivo);
}

char menu() {
    clrscr();
    printf("Escolha uma opção:\n");
    printf("1. Ler script SQL de um arquivo de texto\n");
    printf("2. Digitar um comando SQL\n");
    printf("3. Sair\n");
    printf("Opção: ");

    return getche();
}

int main() {
    pontBD *banco = NULL;
    char comando[1024], escolha;
  
    printf("Simulador de Sistema Gerenciador de Banco de Dados\n");

    do {

        escolha = menu();
        switch (escolha) {
            case '1':
                {
                    char nomeArquivo[256];
                    printf("Digite o caminho completo do arquivo de script: ");
                    fgets(nomeArquivo, sizeof(nomeArquivo), stdin);

                    // Remova a quebra de linha
                    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0';

                    carregarScriptDeCriacao(&banco, nomeArquivo);
                    break;
                }
            case '2':
                {
                    printf("Digite um comando SQL (ou 'SAIR' para voltar ao menu principal):\n");
                    fgets(comando, sizeof(comando), stdin);

                    // Remova a quebra de linha
                    comando[strcspn(comando, "\n")] = '\0';

                    if (strcmp(comando, "SAIR") != 0) {
                        executarComandoSQL(&banco, comando);
                    }
                    break;
                }
            case '3':
                printf("Encerrando o programa.\n");
                break;
            
        }
        getchar();

    } while (escolha != '3');



    return 0;
}
