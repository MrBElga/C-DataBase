#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "tad.h"

void clearString(char line[])
{
	int i;
	for (i = 0; i < strlen(line); i++)
		line[i] = ' ';
}
char getComando(char line[50], char comando[50])
{
	int cont = 0, i;
	char flag = 1;
	for (i = 0; i < strlen(comando) && cont <= 1; i++)
	{

		if (comando[i] != line[i])
			flag = 0;

		if (line[i] == ' ')
			cont++;
	}
	return flag;
}
void getNomeCampo(char line[50], char *aux)
{
	int i = 0;
	int cont = 0;
	for (i = 0; i < strlen(line) && cont <= 1; i++)
	{
		if (line[i] == ' ')
			cont++;

		aux[i] = line[i];
	}
}

void getNomeTabela(char line[50], char *nome)
{
	int i = 0, j = 0, linha = strlen(line);
	int cont = 0;
	for (i = 0; i < linha; i++)
	{

		if (cont >= 2 && line[i] != '(' && line[i] != ' ' && line[i] != ';' && line[i] != 10)
		{
			nome[j] = line[i];
			j++;
		}

		if (line[i] == ' ')
			cont++;
	}
	nome[j] = '\0';
}

void getTipo(char line[50], char *tipo)
{

	int i, cont = 0, j = 0, linha = strlen(line);
	for (i = 0; i < linha; i++)
	{

		if (line[i] == ' ')
			cont++;

		if (cont >= 2 && line[i] != ',')
		{
			tipo[j] = line[i];
			j++;
		}
	}
}

void lerComandos(pontBD **b)
{
	FILE *Arq = fopen("script.txt", "r");
	char line[50], nome[50], tipo[50], database[50];

	char flag = 0;
	fgets(line, sizeof(line), Arq);
	while (!feof(Arq))
	{

		if (flag && !getComando(line, ");"))
		{
			clearString(nome);
			// clearString(tipo);
			getNomeCampo(line, nome);
			// getTipo(line,tipo);
			// printf("%s\n",nome);
		}

		if (getComando(line, "CREATE TABLE "))
		{
			// getNomeTabela(line);
			flag = 1;
		}
		if (getComando(line, "CREATE DATABASE "))
		{
			getNomeTabela(line, database);
			printf("%s", database);
			CadastrarBanco(b, database);
		}
		if (getComando(line, ");"))
		{
			flag = 0;
		}

		fgets(line, sizeof(line), Arq);
	}
	fclose(Arq);
}

int main()
{
    pontBD *banco = NULL;

    // Criar um banco de dados "TestDB"
    CadastrarBanco(&banco, "TestDB");

    // Criar uma tabela "Usuarios"
    CadastrarTabela(&(banco->PTabelas), "Usuarios");

    // Criar campos na tabela "Usuarios"
    CadastrarCampoNaTabela(&(banco->PTabelas), "Usuarios", "ID", 'I', 'S');
    CadastrarCampoNaTabela(&(banco->PTabelas), "Usuarios", "Nome", 'T', 'N');
    CadastrarCampoNaTabela(&(banco->PTabelas), "Usuarios", "Idade", 'I', 'N');

    // Inserir alguns dados na tabela "Usuarios"
    union UDados dado0;
    dado0.ValorI = 1;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "ID"), 'I', dado0);
    strcpy(dado0.ValorT, "Alice");
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Nome"), 'T', dado0);
    dado0.ValorI = 25;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Idade"), 'I', dado0);

    dado0.ValorI = 2;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "ID"), 'I', dado0);
    strcpy(dado0.ValorT, "Bob");
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Nome"), 'T', dado0);
    dado0.ValorI = 30;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Idade"), 'I', dado0);

    dado0.ValorI = 3;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "ID"), 'I', dado0);
    strcpy(dado0.ValorT, "Charlie");
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Nome"), 'T', dado0);
    dado0.ValorI = 35;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Idade"), 'I', dado0);

    // Exibir a tabela antes das exclusões
    printf("Tabela antes das exclusoes:\n");
    ExibirTodasAsTabelas(banco);

    // Deletar um campo da tabela "Usuarios"
    char nomeCampo[] = "Nome";
    DeletarCampo(&(banco->PTabelas->Pcampos), nomeCampo);

    // Exibir a tabela após a exclusão do campo
    printf("\nTabela apos a exclusao do campo 'Nome':\n");
    ExibirTodasAsTabelas(banco);

    // Apagar a tabela "Usuarios"
    char nomeTabela[] = "Usuarios";
    DeletarTabela(banco, nomeTabela);

    // Exibir o banco de dados após a exclusão da tabela
    printf("\nBanco de dados apos a exclusao da tabela 'Usuarios':\n");
    ExibirTodasAsTabelas(banco);

    // Liberar o banco de dados
    LiberarBanco(&banco);

    printf("\nBanco de dados apos excluir o banco':\n");
	ExibirBancos(banco);
    return 0;
}
