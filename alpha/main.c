#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "tad.h"

int main()
{

    setlocale(LC_ALL, "Portuguese");
    pontBD *bancos = NULL;

    // Cadastrar bancos
    CadastrarBannco(&bancos, "db_locutora");

    // Cadastrar tabelas no primeiro banco
    CadastrarTabela(&(bancos->PTabelas), "cliente");
    CadastrarTabela(&(bancos->PTabelas), "aluguel");
    CadastrarTabela(&(bancos->PTabelas), "veiculo");

    // Cadastrar campos tabela cliente
    CadastrarCampoNaTabela(&(bancos->PTabelas), "cliente", "id_cliente", 'I', 'N');
    CadastrarCampoNaTabela(&(bancos->PTabelas), "cliente", "nome", 'T', 'N');
    CadastrarCampoNaTabela(&(bancos->PTabelas), "cliente", "cpf", 'T', 'N');
    CadastrarCampoNaTabela(&(bancos->PTabelas), "cliente", "celular", 'T', 'N');

    // Cadastrar campos tabela aluguel
    CadastrarCampoNaTabela(&(bancos->PTabelas), "aluguel", "id_aluguel", 'I', 'N');
    CadastrarCampoNaTabela(&(bancos->PTabelas), "aluguel", "id_client", 'I', 'S');
    CadastrarCampoNaTabela(&(bancos->PTabelas), "aluguel", "id_veiculo", 'I', 'S');
    CadastrarCampoNaTabela(&(bancos->PTabelas), "aluguel", "dt_saida", 'D', 'N');

     // Cadastrar campos tabela veiculo
    CadastrarCampoNaTabela(&(bancos->PTabelas), "veiculo", "id_veiculo", 'I', 'N');
    CadastrarCampoNaTabela(&(bancos->PTabelas), "veiculo", "marca", 'T', 'S');
    CadastrarCampoNaTabela(&(bancos->PTabelas), "veiculo", "modelo", 'T', 'S');
    CadastrarCampoNaTabela(&(bancos->PTabelas), "veiculo", "placa", 'T', 'N');

    // Cadastrar dados em campos cliente
    PCampos *tabela1Campos = bancos->PTabelas->Patual;
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorI = 1});
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorI = 2});
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorI = 3});

    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorT = "Jose da Silva"});
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorT = "Ana Maria"});
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorT = "Joao Paulo"});

    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorT = "111.111.111-11"});
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorT = "222.222.222-22"});
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorT = "333.333.333-33"});

    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorT = "91111-1111"});
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorT = "92222-2222"});
    CadastrarDadosNaTabela(tabela1Campos, (union UDados){.ValorT = "93333-3333"});

    // Exibir bancos e suas tabelas
    printf("Bancos cadastrados:\n");
    ExibirBancos(bancos);

    printf("\nTabelas cadastradas:\n");
    ExibirTabelas(bancos->PTabelas);

    // Exibir campos e dados
    ExibirTodasAsTabelas(bancos);

    // Aguarda a��o do usu�rio antes de encerrar
    getchar();

    return 0;
}

