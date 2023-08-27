#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"

int main()
{
    pontBD *banco = NULL;
    CadastrarBannco(&banco, "MeuBanco");

    CadastrarTabela(&(banco->PTabelas), "Clientes");

    CadastrarCampoNaTabela(&(banco->PTabelas), "Clientes", "ID", 'I', 'S');
    CadastrarCampoNaTabela(&(banco->PTabelas), "Clientes", "Nome", 'T', 'N');
    CadastrarCampoNaTabela(&(banco->PTabelas), "Clientes", "Idade", 'I', 'N');

    union UDados dado0;
    dado0.ValorI = 1;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "ID"), 'I', dado0);

    union UDados dado1;
    dado1.ValorI = 25;
    printf("\n%d\n", dado1.ValorI);
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "Idade"), 'I', dado1);

    union UDados dado2;
    strcpy(dado2.ValorT, "Joao");
    printf("\n%s\n", dado2.ValorT);
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "Nome"), 'T', dado2);

    printf("\nExibindo Dados\n");
    ExibirTodasAsTabelas(banco);

    union UDados buscaDado;
    buscaDado.ValorI = 25;

    PDados *resultadoBusca = BuscaDados(buscaCampoPorNome(banco->PTabelas->Patual, "Idade")->ValorT, buscaDado);

    if (resultadoBusca != NULL)
    {
        printf("\nDado encontrado:\n");
        printf("Campo: Idade\n");
        printf("Valor: %d\n", resultadoBusca->UDados.ValorI);
    }
    else
    {
        printf("\nDado não encontrado.\n");
    }


    return 0;
}
