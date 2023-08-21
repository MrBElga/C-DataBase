#include <conio2.h>
#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tad.h"
int main()
{
    PCampos *campos = NULL;

    // Cadastrar campos
    CadastrarCampos(&campos, "Nome", 'T', 'N');
    CadastrarCampos(&campos, "Idade", 'I', 'N');

    // Cadastrar mais campos
    CadastrarCampos(&campos, "Salário", 'N', 'N');

    // Cadastrar dados nos campos
    CadastrarDados(campos, (union UDados){.ValorT = "Daniel"});
    CadastrarDados(campos, (union UDados){.ValorI = 22});

    // Cadastrar dados nos novos campos
    CadastrarDados(campos, (union UDados){.ValorN = 1500.75});

    // Exibir campos e dados
    printf("Campos cadastrados:\n");
    ExibirCampos(campos);

    printf("\nDados cadastrados:\n");
    ExibirDados(campos);

    // Restante do código...

    return 0;
}

