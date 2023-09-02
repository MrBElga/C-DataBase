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
    dado0.ValorI = 0;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "ID"), 'I', dado0);

    dado0.ValorI = 25;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "Idade"), 'I', dado0);

    strcpy(dado0.ValorT, "Joao");
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "Nome"), 'T', dado0);

    dado0.ValorI = 1;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "ID"), 'I', dado0);

    dado0.ValorI = 31;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "Idade"), 'I', dado0);

    strcpy(dado0.ValorT, "Jerco");
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "Nome"), 'T', dado0);

    dado0.ValorI = 2;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "ID"), 'I', dado0);

    dado0.ValorI = 50;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "Idade"), 'I', dado0);

    strcpy(dado0.ValorT, "Raposo");
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Patual, "Nome"), 'T', dado0);

    printf("\nExibindo Dados\n");
    ExibirTodasAsTabelas(banco);

    union UDados buscaDado;
    buscaDado.ValorI = 31;

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

    ExibirLinha(&(banco->PTabelas->Patual));
    // ExibirLinha(&(banco->PTabelas->Patual));

    // tratar caso valor nulo
    strcpy(dado0.ValorT, "Joao");
    PDados *dadoParaAlterar = BuscaDados(buscaCampoPorNome(banco->PTabelas->Patual, "Nome")->ValorT, dado0);
    printf("%s", dadoParaAlterar->UDados.ValorT);
    AlterarDado(dadoParaAlterar, "Turista");

    ExibirLinha(&(banco->PTabelas->Patual));

    pontBD *BancoAlt = buscaBancoPorNome(banco, "MeuBanco");
    ;
    AlterarBanco(BancoAlt, "Clientes");

    ExibirBancos(banco);

    PTabelas *TabAlt = buscaTabelaPorNome(banco, "Clientes");
    AlterarTabela(TabAlt, "Clientes0");
    ExibirTabelas(banco->PTabelas);

    PCampos *CampoAlt = buscaCampoPorNome(buscaTabelaPorNome(banco, "Clientes0")->Patual, "Idade");
    AlterarCampo(CampoAlt, "Idade0");
    ExibirCampo(banco->PTabelas->Patual, "Idade0");

    return 0;
}
