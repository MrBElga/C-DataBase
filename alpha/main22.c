#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "tad.h"

void clearString(char line[])
{
	int i;
	for(i=0;i<strlen(line);i++)
		line[i] =' ';
}

void removeSpace(char *tipo){
	int i,cont=0,j=0;
	
	for(i=0;i<strlen(tipo);i++)
	{
		if(tipo[i]==' ')
			cont++;
		
		if(cont <=1 && tipo[i]!=' ')
		{
			tipo[j] = tipo[i];
			j++;
		}
			
	}
	
}
char getComando(char line[50], char comando[50])
{
	int cont =0,i;
	char flag=1;
	for(i=0;i<strlen(comando) && cont <=1;i++){
		
			
		if(comando[i]!=line[i])
			flag=0;
			
		if(line[i]==' ')
			cont++;	
	}	
	return flag;

}
void getNomeCampo(char line[50],char *aux)
{
	int i=0,j=0;
	int cont=0;
	char nome[50];
	for(i=0;i<strlen(line) && cont <=1 ;i++)
	{		
		if(line[i]==' ')
		  cont++;
		
		if(line[i]!=' ')
		{
			aux[j] = line[i];
			j++;	
		}
				
	}
	aux[j] = '\0';
}

void getNomeTabela(char line[50],char *nome)
{
	int i=0,j=0;
	int cont=0;
	for(i=0;i<strlen(line);i++)
	{
		
		if(cont >=2 && line[i]!='(' && line[i]!=' ' && line[i]!=';' && line[i]!=10)
		{
			nome[j] = line[i];
			j++;
		}
		
	
		if(line[i]==' ')
			cont++;
	
		
	}
	nome[j] = '\0';

}

void getTipo(char line[50],char *tipo){
	
	int i,cont=0,j=0;
	char aux[50];
	for(i=0;i<strlen(line);i++){
		
		if(line[i]== ' ')
			cont++;
			
		if(cont >=2 &&  line[i]!= ',')
		{
			tipo[j] = line[i];
			j++;
		}
		
	}
	tipo[j] = '\0';
}

void getDado(char dado[],int *cont,char line[])
{
	int i,j=0,qtd=0,cont2=0;
	char flag=0,flag2=1;
	for(i=0;i<strlen(line) && flag2 ;i++)
	{
		if(cont2 >=2)
		{
			flag=1;
			if(flag && line[i]==',')
				qtd++;
			
			if(flag && line[i]!=')' && line[i]!=',' && line[i]!=';' && qtd >= *cont)
			{
				dado[j] = line[i];
				j++;
			}	
		

			if(qtd > *cont)
			{	
			   	if(line[i]==',' || line[i]==')')
				{
					dado[j] ='\0';
					(*cont)++;
					flag2=0;
				}
			}
			
		}
		
		if(line[i]=='(')
			cont2++;
	}
}
void alterTable(char line[50],char nome[],int espaco)
{
	int i,cont=0,j=0;
	for(i=0;i<strlen(line);i++){
		
			if(line[i]== ' ')
				cont++;
			
			if(cont >=espaco && cont < espaco+1 && line[i]!=' ' && line[i]!=';')
			{
					nome[j] = line[i];
					j++;
			}
	}
	nome[j] = '\0';
}

void getColuna(char line[],char *aux,PTabelas**Tab,pontBD*banco)
{
	char flag=0;
	char dados[50],nome[50],test;
	int i,cont=0,j=0,cont2=0;
	PCampos*campos = NULL;
	PTabelas*tabela = NULL;
	union UDados d;
	alterTable(line,nome,2);
    tabela =  buscaTabelaPorNome(banco,nome);
	for(i=0;i<strlen(line);i++)
	{
		if(flag && line[i]!=')' && line[i]!=',' && cont <= 1)
		{
			aux[j] = line[i];
			j++;
		}	
		
		if(line[i]=='(')
		{
			flag=1;
			cont++;
		}		
		if(cont==1)
		{
			if(line[i]==',' || line[i]==')')
			{
				aux[j] = '\0';
				j=0;
				if(buscaCampoPorNome(tabela->Pcampos,aux))
				{
					getDado(dados,&cont2,line);
			
					campos = buscaCampoPorNome(tabela->Pcampos,aux);
					if(campos->Tipo=='I')
					{
						d.ValorI = atoi(dados);
						CadastrarDadosNaTabela(campos,'I',d);
					}
			
					if(campos->Tipo=='N')
					{
						d.ValorN = atof(dados);
						CadastrarDadosNaTabela(campos,'N',d);
					}
							
					if(campos->Tipo=='D')
					{
						strcpy(d.ValorD,dados);
						CadastrarDadosNaTabela(campos,'D',d);
					}	
					if(campos->Tipo=='C')
					{
						d.ValorC = dados[0];
						CadastrarDadosNaTabela(campos,'C',d);
					}						
					if(campos->Tipo=='T')
					{
						strcpy(d.ValorT,dados);
						CadastrarDadosNaTabela(campos,'T',d);
					}
						
				}	
				clearString(dados);
				clearString(aux);
			}			
		}		
		if(line[i]==')')
			flag=0;
	}
}


int counter(char comando[]){
	
	int i;
	char flag=0;
	int cont=0;
	
	for(i=0;i<strlen(comando)-1;i++)
	{
		if(flag && comando[i]!=')' && comando[i]!=' ')
			cont++;
			
		if(comando[i]=='(')
			flag=1;
	
	}
	
	return cont;	
}


void lerComandos(pontBD **b,PCampos**campos,PTabelas**Tab)
{
	FILE*Arq = fopen("script.txt","r");
	char line[100],nome[50],tipo[50],database[50],tabela[50],aux[100];
	char t;
	char flag=0;
	fgets(line,sizeof(line),Arq);
	while(!feof(Arq))
	{
		
		if(flag && !getComando(line,");"))
		{
			clearString(nome);
			getNomeCampo(line,nome);
				
			getTipo(line,tipo);
			removeSpace(tipo);
			if(getComando(tipo,"INTEGER"))
				t= 'I';
				
			if(getComando(tipo,"CHARACTER"))
			{
				if(counter(tipo)>=2)
					t='T';
				else
					t='C';
			}	
			if(getComando(tipo,"DATE"))
				t='D';
			if(getComando(tipo,"NUMERIC"))
				t='N';
			
			if(!getComando(nome,"CONSTRAINT"))
				CadastrarCampoNaTabela(Tab,tabela,nome,t,'N');

		}	
			
		if(getComando(line,"CREATE TABLE "))
		{
			getNomeTabela(line,tabela);
			//printf("%s\n",tabela);
			CadastrarTabela(Tab,tabela);
			(*b)->PTabelas = *Tab;
			flag=1;
		}
		if(getComando(line,"CREATE DATABASE "))
		{
			getNomeTabela(line,database);
			CadastrarBanco(b,database);
		}	
		if(getComando(line,");"))
		{
			flag=0;
		}
		
		if(getComando(line,"ALTER TABLE "))
		{
			alterTable(line,nome,6);
		}
		
		if(getComando(line,"insert into"))
		{
			alterTable(line,nome,2);
			getColuna(line,aux,Tab,*b);
		}
		
		
		if(getComando(line,"select *"))
		{
			clearString(tabela);
			alterTable(line,tabela,3);
			selectAll(*Tab,nome);

		}
		
		fgets(line,sizeof(line),Arq);	
	}
	fclose(Arq);
}

int main() 
{
	char test[50];
	pontBD *banco = NULL;
	PCampos*campos = NULL;
	PTabelas*tabela = NULL;
	lerComandos(&banco,&campos,&tabela);
	

	//exibir(banco);
    return 0;
}
