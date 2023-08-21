#include <conio2.h>
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tad.h"

int main()
{
    PDados *dados = NULL;
    CadastrarDados(&dados, (union UDados){.ValorI = 42});
    CadastrarDados(&dados, (union UDados){.ValorN = 3.14});

    PCampos *campos = NULL;
    CadastrarCampos(&campos, "Nome", 'C', 'N');
    CadastrarCampos(&campos, "Idade", 'I', 'N');

    PTabelas *tabelas = NULL;
    CadastrarTabela(&tabelas, "Pessoas");
    CadastrarTabela(&tabelas, "Produtos");

    printf("Dados cadastrados:\n");
    ExibirDados(dados);

    printf("\nCampos cadastrados:\n");
    ExibirCampos(campos);   
    return 0;
}