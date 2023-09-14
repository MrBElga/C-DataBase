#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "tad.h"


// para executar um comando SQL
#include <stdio.h>
#include <string.h>

void executarComandoSQL(pontBD **banco, const char *comando) 
{
    char comandoCopy[100];
    char token[100];  // Changed token to an array
    strcpy(comandoCopy, comando);
    strcpy(token, comando);  // Copy the command to token

    // Tokenize the command to extract the first word
    char *tokenPtr = strtok(token, " ");
    
    if (tokenPtr == NULL)
    {
        printf("Comando SQL nao reconhecido: %s\n", comando);
        return;
    }

    if (strcmp(tokenPtr, "CREATE") == 0) 
    {
        printf("Executando CREATE TABLE...\n");
    } 
    else if (strcmp(tokenPtr, "INSERT") == 0) 
    {
        printf("Executando INSERT INTO...\n");
    } 
    else if (strcmp(tokenPtr, "UPDATE") == 0) 
    {
        printf("Executando UPDATE...\n");
    } 
    else if (strcmp(tokenPtr, "DELETE") == 0) 
    {
        printf("Executando DELETE FROM...\n");
    } 
    else if (strcmp(tokenPtr, "SELECT") == 0)
    {
        printf("Executando SELECT...\n");
    } 
    else if (strcmp(tokenPtr, "SAIR") == 0) 
    {

        printf("Encerrando o programa...\n");
    } 
    else 
    {
        printf("Comando SQL não reconhecido: %s\n", comando);
    }
    getchar();
}

void carregarScriptDeCriacao(pontBD **banco, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
      
        linha[strcspn(linha, "\n")] = '\0';

       
        executarComandoSQL(banco, linha);
    }

    fclose(arquivo);
}

char menu() {
    system("cls");
    printf("[1] Ler script SQL de um arquivo de texto\n");
    printf("[2] Digitar um comando SQL\n");
    printf("[ESC] Sair\n");
    printf("Opcao: ");

    return getche();
}

int main() 
{
    pontBD *banco = NULL;
    char comando[100], nomeArquivo[100], op;
  
    printf("Simulador de Sistema Gerenciador de Banco de Dados\n");

    do {

        op = menu();
        switch (op) {
            case '1':
                {
                    
                    printf("Digite o caminho completo do arquivo de script: ");
                    fgets(nomeArquivo, sizeof(nomeArquivo), stdin);

                

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
      
    } while (op != 27);



    return 0;
}
