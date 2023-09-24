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

	// lerComandos(&banco);
	printf("\n");
	// ExibirBancos(banco);
    CadastrarBanco(&banco, "MeuBanco");
    CadastrarTabela(&(banco->PTabelas), "Clientes");

    
    CadastrarCampoNaTabela(&(banco->PTabelas), "Clientes", "ID", 'I', 'S');
    CadastrarCampoNaTabela(&(banco->PTabelas), "Clientes", "Nome", 'T', 'N');
    CadastrarCampoNaTabela(&(banco->PTabelas), "Clientes", "Idade", 'I', 'N');

  
    union UDados dado0;
    dado0.ValorI = 0;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "ID"), 'I', dado0);

    dado0.ValorI = 25;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Idade"), 'I', dado0);

    strcpy(dado0.ValorT, "Joao");
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Nome"), 'T', dado0);

    dado0.ValorI = 1;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "ID"), 'I', dado0);

    dado0.ValorI = 31;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Idade"), 'I', dado0);

    strcpy(dado0.ValorT, "Jerco");
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Nome"), 'T', dado0);
	
	dado0.ValorI = 2;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "ID"), 'I', dado0);

    dado0.ValorI = 45;
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Idade"), 'I', dado0);

    strcpy(dado0.ValorT, "Raposo");
    CadastrarDadosNaTabela(buscaCampoPorNome(banco->PTabelas->Pcampos, "Nome"), 'T', dado0);
    printf("\nTabela antes da exclusao:\n");
    ExibirTodasAsTabelas(banco);

   
  
	char nomeCampo[] = "Nome"; 

	strcpy(dado0.ValorT, "Joao"); 
 	DeletarLinha(&banco, "Clientes", nomeCampo, dado0);
    strcpy(dado0.ValorT, "Jerco");
	DeletarLinha(&banco, "Clientes", nomeCampo, dado0);


  
    printf("\nTabela depois da exclusao:\n");
    ExibirTodasAsTabelas(banco);

	printf("\nTabela depois da exclusao e cadastro:\n");
    ExibirTodasAsTabelas(banco);
   
    free(banco);

	return 0;
}
