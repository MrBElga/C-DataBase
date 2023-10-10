#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <windows.h>
#include "tad.h"

void clearString(char line[])
{
	int i;
	for(i=0;i<strlen(line);i++)
		line[i] =' ';
}

void remover(char line[])
{
	int i,j=0;
	int cont =0;
	for(i=0;i<strlen(line);i++)
	{
		if(cont >=1)
		{
			line[j] = line[i];
			j++;
		}
		
		
		if(line[i]==' ')
			cont++;
		
			
	}
	line[j] = '\0';
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
	tipo[j] = '\0';
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
			
			if(flag && line[i]!=')' && line[i]!=',' && line[i]!=';' && qtd >= *cont && line[i]!=39)
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
	dado[j] = '\0';
	
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
	j=0;
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
			if(line[i]==',' || line[i]==')' || line[i]==' ')
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
						removeSpace(dados);
						strcpy(d.ValorD,dados);
						CadastrarDadosNaTabela(campos,'D',d);
					}	
					if(campos->Tipo=='C')
					{
						d.ValorC = dados[strlen(dados)-1];
						CadastrarDadosNaTabela(campos,'C',d);
					}						
					if(campos->Tipo=='T')
					{
						remover(dados);
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

int contaEspaco(char line[])
{
	int cont=0;
	int i;
	for(i=0;i<strlen(line);i++)
	{
		if(line[i]==' ')
			cont++;
	}
	return cont;
}
void update(char line[],PTabelas**Tab)
{
	int i,espaco=0,j=0,k=0,cont;
	char campo[50],dado[50],nomeCampo[50],tabela[50],tipo[50];
	char flag=1;
	PTabelas*TabAux;
	PCampos*CampoAux,*aux;
	union UDados dadosAux;
	
	cont = contaEspaco(line);
	alterTable(line,tabela,1);
	TabAux = buscaTab(*Tab,tabela);
	alterTable(line,tipo,cont);
	alterTable(line,campo,cont-2);
	CampoAux = buscaCampoPorNome(TabAux->Pcampos,campo);
	if(CampoAux)
	{
		if(CampoAux->Tipo == 'I')
			dadosAux.ValorI = atoi(tipo);
		if(CampoAux->Tipo == 'N')
			dadosAux.ValorN = atof(tipo);
		if(CampoAux->Tipo == 'T')
			strcpy(dadosAux.ValorT,tipo);
		if(CampoAux->Tipo == 'D')
			strcpy(dadosAux.ValorD,tipo);
		if(CampoAux->Tipo == 'C')
			dadosAux.ValorC = tipo[0];
	
	}
	for(i=0;i<strlen(line);i++)
	{
		if(line[i]==' ')
			espaco++;
			
		if(espaco >= 3)
		{
			if(line[i]!=' ' && line[i]!='=' && flag && line[i]!=',')
			{
				campo[j] = line[i];
				j++;
				
			}
			if(line[i]!=' ' && line[i]!='=' && !flag && line[i]!=',' )
			{
				dado[k] = line[i];
				k++;
			}
			
			if(line[i]==',' || line[i+1]=='W')
			{
				flag=1;
				dado[k] = '\0';
				k=0;
				CampoAux = buscaCampoPorNome(TabAux->Pcampos,campo);
				if(CampoAux)
				{
					AlterarDado(CampoAux,dado,dadosAux,TabAux);
				}
					

			}
		}
			
		if(line[i]=='=')
		{
			flag=0;
			campo[j] = '\0';
			j=0;
		}
			
	}
}

void getForeign(char line[], char campo[])
{
	int i,j=0,cont=0;
	char flag=0;
	
	for(i=0;i<strlen(line);i++)
	{
		
		if(flag && cont  == 1) 
		{
			if(line[i]!=' ' && line[i]!=')')
			{
				campo[j] = line[i];
				j++; 
			}
			
		}
		if(line[i]==')')
			flag=0;
		
		if(line[i]=='(')
		{
			flag=1;
			cont++;
		}
		
	}
	campo[j] = '\0';
}

void updatePK(char line[], char tabela[],PTabelas**tab)
{
	int i,j=0;
	char flag=0,aux[50];
	PCampos*campo = NULL;
	PTabelas*tabAux = buscaTab(*tab,tabela);
	for(i=0;i<strlen(line);i++)
	{
		
		if(line[i]!=' ' && line[i]!=',')
		{
			aux[j] = line[i];
			j++;
		}
		
		if(line[i]==',')
		{
			aux[j] = '\0';
			campo = buscaCampoPorNome(tabAux->Pcampos,aux);
			if(campo)
				campo->PK = 'S';
			j=0;	
		}
			
	}
	aux[j] = '\0';
	campo = buscaCampoPorNome(tabAux->Pcampos,aux);
	if(campo)
		campo->PK = 'S';
}

void lerComandos(pontBD **b,PCampos**campos,PTabelas**Tab,char caminho[],char f)
{
	FILE*Arq=NULL;
	PTabelas*TabAux,*alterAux=NULL;
	PCampos*CampoAux;
	union UDados dadosAux;
	char line[200],nome[50],tipo[50],database[50],tabela[50],aux[100],nomeCampo[50];
	char comando[50];
	char t;
	int v1,v2;
	char flag=0;
	
	if(f==1)
	{
		Arq = fopen(caminho,"r");
		fgets(line,sizeof(line),Arq);
	}
	else
	{
			clrscr();
			desenhar(60,5,150,20);
			desenhar(61,10,149,12);
			gotoxy(62,9);
			textcolor(RED);
			printf("Digite o comando: ");
			textcolor(WHITE);
			gotoxy(62,11);
			gets(line);
	}

	while((!feof(Arq) && Arq!=NULL) || strcmp(line,"\0")!=0)
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
			else
			{
				getForeign(line,nome);
				updatePK(nome,tabela,Tab);
			}

		}	
			
		if(getComando(line,"CREATE TABLE "))
		{
			getNomeTabela(line,tabela);
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
		if(getComando(line,"    FOREIGN"))
		{
			alterAux = buscaTabelaPorNome(*b,nome);
			if(alterAux)
			{
				getForeign(line,nome);
				CampoAux = buscaCampoPorNome(alterAux->Pcampos,nome);
				if(CampoAux)
				{
					alterTable(line,tabela,8);
					alterAux = buscaTabelaPorNome(*b,tabela);
					if(alterAux)
					{
						if(buscaCampoPorNome(alterAux->Pcampos,nome))
							CampoAux->FK = buscaCampoPorNome(alterAux->Pcampos,nome);
					}
					
				}
			}
		}
		if(getComando(line,"INSERT INTO"))
		{
			alterTable(line,nome,2);
			getColuna(line,aux,Tab,*b);
		}
	
		if(getComando(line,"SELECT *"))
		{
			alterTable(line,tabela,3);
			alterTable(line,comando,6);
			if(strcmp(comando,"BETWEEN")==0)
			{
				alterTable(line,comando,contaEspaco(line)-2);
				v1 = atoi(comando);
				alterTable(line,comando,contaEspaco(line));
				v2 = atoi(comando);
				alterTable(line,comando,(contaEspaco(line)-contaEspaco(line))+5);
				selectBet(*Tab,v1,v2,tabela,comando);
				getch();
				system("cls");
			}
			clearString(comando);
			alterTable(line,comando,6);
			if(strcmp(comando,"BETWEEN")!=0)
			{
				selectAll(*Tab,tabela);
				getch();
				system("cls");
			}

		}
		if(getComando(line,"DELETE"))
		{
			alterTable(line,tabela,2);
			TabAux = buscaTab(*Tab,tabela);
			alterTable(line,nomeCampo,4);
			CampoAux = buscaCampoPorNome(TabAux->Pcampos,nomeCampo);
			alterTable(line,tipo,6);
			
			if(CampoAux->Tipo == 'I')
				dadosAux.ValorI = atoi(tipo);
			if(CampoAux->Tipo == 'N')
				dadosAux.ValorN = atof(tipo);
			if(CampoAux->Tipo == 'T')
				strcpy(dadosAux.ValorT,tipo);
			if(CampoAux->Tipo == 'D')
				strcpy(dadosAux.ValorD,tipo);
			if(CampoAux->Tipo == 'C')
				dadosAux.ValorC = tipo[0];
			
			DeletarLinha(b,tabela,nomeCampo,dadosAux);
		}
		
		if(getComando(line,"UPDATE"))
		{
			update(line,Tab);
		}
		
		if(f==1)
			fgets(line,sizeof(line),Arq);
		else
		{
			clrscr();
			desenhar(60,5,150,20);
			desenhar(61,10,149,12);
			gotoxy(62,9);
			textcolor(RED);
			printf("Digite o comando: ");
			textcolor(WHITE);
			gotoxy(62,11);
			gets(line);
		}
		if(feof(Arq))
			strcpy(line,"\0");
	}
	
	fclose(Arq);
}

char Menu(pontBD *banco)
{
	int i =0;
	PTabelas *tabelas=NULL;
	clrscr();

	textcolor(RED);
	gotoxy(85,4);
	printf("DINAMICO-C-SGBD");
	gotoxy(85,7);
	textcolor(RED);
	printf("## ");
	textcolor(WHITE);
	printf("MENU ");
	textcolor(RED);
	printf("##");
	gotoxy(62,11);
	textcolor(BLUE);
	printf("[1]");
	textcolor(RED);
	printf("   - ");
	textcolor(WHITE);
	printf("DIGITAR COMANDO SQL");
	gotoxy(62,13);
	textcolor(BLUE);
	printf("[2]");
	textcolor(RED);
	printf("   - ");
	textcolor(WHITE);
	printf("DIGITAR CAMINHO PARA BOLOCO DE NOTAS");
	gotoxy(62,15);
	textcolor(BLUE);;
	printf("[ESC]");
	textcolor(RED);
	printf(" - ");
	textcolor(WHITE);
	printf("SAIR");

	gotoxy(122,6);
	textcolor(WHITE);
	printf("Banco: ");
		
	gotoxy(122,13);
	printf("Tabelas");
	if(banco==NULL)
	{
	
		
		gotoxy(122,8);
		textcolor(RED);
		printf("SEM BANCO");
		gotoxy(122,15);;
		printf("SEM TABELAS");
	}
	else
	{
	
		gotoxy(122,8);
		textcolor(GREEN);
		printf("%s",banco->Banco_Dados);

		if(banco->PTabelas!=NULL)
		{
			i=15;
			tabelas=banco->PTabelas;
			while(tabelas!=NULL)
			{
				gotoxy(122,i);
				printf("%s",tabelas->Tabela);
				tabelas = tabelas->prox;
				i++;
			}
			if(i>19)
			{
				gotoxy(122,18);
				printf("                 ");
				gotoxy(122,18);
				printf("+%d",i-18);
			}
		
		}
		else
		{
			gotoxy(123,15);
			textcolor(RED);
			printf("SEM TABELAS");
		}
			
			
	}
	textcolor(BLACK);
	//borda externa
	desenhar(60,5,120,20);
	//borda interna Banco
	desenhar(61,6,119,8);
	//borda Interna
	desenhar(61,9,119,19);
	//borda externa dir
	desenhar(120,5,140,20);
	//borda interna dir 
	desenhar(121,14,139,19);
	//borda interna tabelas
	desenhar(121,7,139,12);
	//juntas 
	gotoxy(120,5);
	printf("%c",194);
	gotoxy(120,20);
	printf("%c",193);
 
	
	gotoxy(62,17);
	textcolor(GREEN);
	printf("opcao: ");
	
	textcolor(WHITE);

	return getche();
}

int main() 
{
	system("mode con:cols=200 lines=80"); 
	SetConsoleTitle("DINAMICO-C-SGBD");
	int cor = DARKGRAY;
	char test[50],op,op2,caminho[50];
	
	pintarFundo(cor,200,80);
	 
	
	pontBD *banco = NULL;
	PCampos*campos = NULL;
	PTabelas*tabela = NULL;

	do{
		op = Menu(banco);
		switch(op)
		{
			case '1':
				lerComandos(&banco,&campos,&tabela,"",0);
				getch();
				break;
			case '2':
				clrscr();
				desenhar(60,5,150,20);
				desenhar(61,10,149,12);
				gotoxy(62,9);
				textcolor(RED);
				printf("Digite o caminho: ");
				textcolor(WHITE);
				gotoxy(62,11);
				gets(caminho);
				lerComandos(&banco,&campos,&tabela,caminho,1);
				break;
		}
	}while(op!=27);
	
	exibir(banco);
    return 0;
}
