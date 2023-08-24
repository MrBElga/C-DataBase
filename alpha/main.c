#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "tad.h"

int main()
{
   
    clrscr();
    setlocale(LC_ALL, "Portuguese");
    pontBD *bancos = NULL;

    // Cadastrar bancos
    CadastrarBannco(&bancos, "Banco A");

    // Cadastrar tabelas no primeiro banco
    CadastrarTabela(&(bancos->PTabelas), "Tabela 1");
    CadastrarTabela(&(bancos->PTabelas), "Tabela 2");

    // Cadastrar campos em uma tabela
    CadastrarCampoNaTabela(&(bancos->PTabelas), "Tabela 1", "Nome", 'T', 'N');
    CadastrarCampoNaTabela(&(bancos->PTabelas), "Tabela 1", "Idade", 'I', 'N');

    // Cadastrar campos em outra tabela
    CadastrarCampoNaTabela(&(bancos->PTabelas), "Tabela 2", "Salário", 'N', 'N');

    // Cadastrar dados em campos
    PCampos *tabela1Campos = bancos->PTabelas->Patual;
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorT = "Daniel"});
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorI = 22});

    PCampos *tabela2Campos = bancos->PTabelas->prox->Patual;
    CadastrarDadosNaTabela(tabela2Campos, (union UDados){.ValorN = 1500.75});

    // Exibir bancos e suas tabelas
    printf("Bancos cadastrados:\n");
    ExibirBancos(bancos);

    printf("\nTabelas cadastradas:\n");
    ExibirTabelas(bancos->PTabelas);

    // Exibir campos e dados
    ExibirTodasAsTabelas(bancos);

    // Aguarda ação do usuário antes de encerrar
    getch();

    return 0;
}

