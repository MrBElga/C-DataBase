union UDados
{
    int ValorI;
    float ValorN;
    char ValorD[11], ValorC;
    char ValorT[50];
};

struct PDados
{
    union UDados UDados;
    struct PDados *prox;
};
typedef struct PDados PDados;

struct PCampos
{
    char Campo[30], Tipo, PK;
    struct PDados *Valor, *PAtual;
    struct PCampos *prox, *FK;
};
typedef struct PCampos PCampos;

struct PTabelas
{
    char Tabela[30];
    struct PCampos *Pcampos;
    struct PTabelas *prox, *ant;
};
typedef struct PTabelas PTabelas;

struct pontBD
{
    char Banco_Dados[50];
    struct PTabelas *PTabelas;
};
typedef struct pontBD pontBD;

// Buscas

// Dados [OK]
int BuscaDados(union UDados nDado,PTabelas*tab)
{
    PDados *Dado;
    int cont=0;
    PCampos*aux = tab->Pcampos;
 
        Dado = aux->PAtual;
        while (Dado != NULL)
        {
        
            if (aux->Tipo == 'I')
            {
            	if(Dado->UDados.ValorI == nDado.ValorI)
					return cont;	
       
            }
            cont++;
            Dado = Dado->prox;
        }
    return -1;;
}

// Campos [OK]
PCampos *buscaCampoPorNome(PCampos *campos, char nomeCampo[])
{
    PCampos *atualCampo = campos;

    while (atualCampo != NULL)
    {
        if (strcmp(atualCampo->Campo, nomeCampo) == 0)
        {
            return atualCampo;
        }
        atualCampo = atualCampo->prox;
    }

    return NULL;
}

// Tabelas[OK]
PTabelas *buscaTabelaPorNome(pontBD *banco, char nomeTabela[])
{
    PTabelas *atualTabela = banco->PTabelas;

    while (atualTabela != NULL)
    {
        if (strcmp(atualTabela->Tabela, nomeTabela) == 0)
        {
            return atualTabela;
        }
        atualTabela = atualTabela->prox;
    }

    return NULL;
}
// Banco
pontBD *buscaBancoPorNome(pontBD *listaBancos, char nomeBanco[])
{
    pontBD *atualBanco = listaBancos;

    while (atualBanco != NULL)
    {
        if (strcmp(atualBanco->Banco_Dados, nomeBanco) == 0)
        {
            return atualBanco;
        }
        // adaptar para ter N bancos
        atualBanco = NULL;
    }

    return NULL;
}

// FK

// Cadastros

// cadastra os dados do banco [OK]

PDados *novaCaixaDados(char Tipo, union UDados nDado)
{
    PDados *nova = (PDados *)malloc(sizeof(PDados));
    // if do tipo LEMBRAR
    if (Tipo == 'I')
        nova->UDados.ValorI = nDado.ValorI;
    else if (Tipo == 'T')
        strcpy(nova->UDados.ValorT, nDado.ValorT);
    else if (Tipo == 'D')
        strcpy(nova->UDados.ValorD, nDado.ValorD);
    else if (Tipo == 'C')
        nova->UDados.ValorC = nDado.ValorC;
    else if (Tipo == 'N')
        nova->UDados.ValorN = nDado.ValorN;
    nova->prox = NULL;
    return nova;
}

void CadastrarDados(PDados **pDados, char Tipo, union UDados nDado)
{
    PDados *novaCaixa = novaCaixaDados(Tipo, nDado);

    if (*pDados != NULL)
    {
        PDados *ultimo = *pDados;
        while (ultimo->prox != NULL)
        {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novaCaixa;
    }
    else
    {
        *pDados = novaCaixa;
    }
}

// cadastra os campos do banco [OK/2] (Falta a Foreign Key, possivelmente passar o endeço que a FK-> vai guardar)
PCampos *novoCaixaCampo(char nome[], char Tipo, char PK)
{
    PCampos *nova = (PCampos *)malloc(sizeof(PCampos));
    nova->prox = NULL;
    nova->FK = NULL;
    nova->PAtual = NULL;
    nova->Valor = NULL;
    nova->Tipo = Tipo;
    nova->PK = PK;
    strcpy(nova->Campo, nome);
    return nova;
}

void CadastrarCampos(PCampos **pCampos, char nome[], char Tipo, char PK)
{
    PCampos *novo = novoCaixaCampo(nome, Tipo, PK);
    if (*pCampos == NULL)
    {
        *pCampos = novo;
    }
    else
    {
        PCampos *temp = *pCampos;
        while (temp->prox != NULL)
        {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

// Cadastro tabelas do Banco [OK]
PTabelas *novaCaixaTabela(char nome[])
{
    PTabelas *nova = (PTabelas *)malloc(sizeof(PTabelas));
    strcpy(nova->Tabela, nome);
    nova->Pcampos = NULL;
    nova->prox = nova->ant = NULL;
    return nova;
}

void CadastrarTabela(PTabelas **Tabela, char nome[])
{
    PTabelas *nova = novaCaixaTabela(nome);
    if (*Tabela == NULL)
    {
        *Tabela = nova;
    }
    else
    {
        PTabelas *temp = *Tabela;
        while (temp->prox != NULL)
        {
            temp = temp->prox;
        }
        temp->prox = nova;
        nova->ant = temp;
    }
}

// Cadastrar Banco [OK]
pontBD *NovoCaixaBanco(char nome[])
{
    pontBD *novo = (pontBD *)malloc(sizeof(pontBD));
    strcpy(novo->Banco_Dados, nome);
    novo->PTabelas = NULL;
    return novo;
}

void CadastrarBanco(pontBD **Banco, char nome[])
{
    pontBD *novo = NovoCaixaBanco(nome) /* ,*temp = *Banco */;

    if (*Banco == NULL)
    {
        *Banco = novo;
    }
    else
    {
        // alterar para caso haja mais bancos
        printf("no momento nao possivel cadastrar um banco de dados\n");
        printf("delete o banco atual para cadastrar um novo\n");
        getchar();
    }
}

// Função para cadastrar um novo campo em uma tabela
void CadastrarCampoNaTabela(PTabelas **Tabela, char nomeTabela[], char nomeCampo[], char Tipo, char FK)
{
    PTabelas *tabelaAlvo = *Tabela;
    while (tabelaAlvo != NULL && strcmp(tabelaAlvo->Tabela, nomeTabela) != 0)
    {
        tabelaAlvo = tabelaAlvo->prox;
    }

    if (tabelaAlvo != NULL)
    {
        CadastrarCampos(&(tabelaAlvo->Pcampos), nomeCampo, Tipo, FK);
    }
}

// Função para cadastrar dados em um campo de uma tabela
void CadastrarDadosNaTabela(PCampos *campos, char Tipo, union UDados nDado)
{
    CadastrarDados(&(campos->Valor), Tipo, nDado);
    if (campos->Valor->prox == NULL)
        campos->PAtual = campos->Valor;
}

// Alterar
// Dados
void AlterarDado(PCampos *pCampos,char NovoDado[], union UDados dados,PTabelas*tab)
{
	 PDados*d;
	 int cont=0,qtd;
	 qtd = BuscaDados(dados,tab);
     
     if(qtd!=-1)
	{
		d = pCampos->PAtual;
		while(cont < qtd)
		{
			d = d->prox;
			cont++;
		}
		if(pCampos->Tipo == 'I')
	    	d->UDados.ValorI = atoi(NovoDado);
		if(pCampos->Tipo == 'N')
	    	d->UDados.ValorN = atof(NovoDado);
	    if(pCampos->Tipo == 'T')
	    	strcpy(d->UDados.ValorT,NovoDado);
	    if(pCampos->Tipo == 'D')
	    	strcpy(d->UDados.ValorD,NovoDado);
	    if(pCampos->Tipo == 'C')
	   		 d->UDados.ValorC = NovoDado[0]; 	
		
	}
     	
     	

}

// Campos
void AlterarCampo(PCampos *pCampos, char NovoCampo[])
{
    strcpy(pCampos->Campo, NovoCampo);
}

void AlterarCampoTipo(PCampos *pCampos, char Tipo)
{
    pCampos->Tipo = Tipo;
}

void AlterarCamposPK(PCampos *pCampos, char PK)
{
    pCampos->PK = PK;
}

void AlterarCamposFK(PCampos *pCampos, PCampos *NovaFK)
{
    pCampos->FK = NovaFK;
}
// Tabelas
void AlterarTabela(PTabelas *pTabela, char NovoTabela[])
{
    strcpy(pTabela->Tabela, NovoTabela);
}
// Banco
void AlterarBanco(pontBD *PontBD, char NovoBanco[])
{
    strcpy(PontBD->Banco_Dados, NovoBanco);
}

// Deletar

// deletar linha
int compararDados(union UDados dado1, union UDados dado2, char tipoCampo)
{
    if (tipoCampo == 'I')
    {
        return dado1.ValorI == dado2.ValorI;
    }
    else if (tipoCampo == 'N')
    {
        return dado1.ValorN == dado2.ValorN;
    }
    else if (tipoCampo == 'T')
    {
        return strcmp(dado1.ValorT, dado2.ValorT) == 0;
    }
    else if (tipoCampo == 'C')
    {
        return dado1.ValorC == dado2.ValorC;
    }
    else if (tipoCampo == 'D')
    {
        return strcmp(dado1.ValorD, dado2.ValorD) == 0;
    }
    return 0;
}

void ExcluirLinhaCampo(PCampos *campo, union UDados valor, PTabelas *tabela)
{
    PDados *anterior = NULL;
    PCampos *auxC = tabela->Pcampos;
    int pos = -1, aux = 0, flag = 0;
    while (campo->PAtual != NULL && flag != 1)
    {
        if (compararDados(campo->PAtual->UDados, valor, campo->Tipo))
        {
            if (anterior != NULL)
                anterior->prox = campo->PAtual->prox;
            else
                campo->Valor = campo->PAtual->prox;
            flag = 1;
        }
        pos++;
        anterior = campo->PAtual;
        campo->PAtual = campo->PAtual->prox;
    }
    //printf("%d \t %d\n", pos, flag);
    if (flag == 1)
    {
        while (auxC != NULL)
        {
            if (strcmp(auxC->Campo, campo->Campo) != 0)
            {
                if (pos == 0)
                {
                    if (auxC->PAtual->prox != NULL)
                        auxC->Valor = auxC->PAtual->prox;
                    else
                        auxC->Valor = NULL;
                }
                else
                {
                    aux = 0;
                    while (aux < pos && auxC->PAtual->prox != NULL)
                    {
                        anterior = auxC->PAtual;
                        auxC->PAtual = auxC->PAtual->prox;
                        aux++;
                    }

                    if (anterior != NULL)
                        anterior->prox = auxC->PAtual->prox;
                }
            }
            auxC->PAtual = auxC->Valor;
            auxC = auxC->prox;
        }
    }
}

void DeletarLinha(pontBD **banco, char nomeTabela[], char nomeCampo[], union UDados valor)
{
    PTabelas *tabela = buscaTabelaPorNome(*banco, nomeTabela);
    PCampos *campo = buscaCampoPorNome(tabela->Pcampos, nomeCampo);
    if (tabela == NULL)
    {
        printf("Tabela %s nao encontrada.\n", nomeTabela);
    }
    else
    {
        if (campo == NULL)
        {
            printf("Campo %s nao encontrado na tabela %s.\n", nomeCampo, nomeTabela);
        }
        else
        {
            ExcluirLinhaCampo(campo, valor, tabela);
        }
    }
}

// Campos

void ApagarDados(PDados *pDados)
{
    PDados *atual = pDados, *aux = NULL;
    while (atual != NULL)
    {
        aux = atual->prox;
        free(atual);
        atual = aux;
    }
}

void DeletarCampo(PCampos **pCampos, char nomeCampo[])
{
    PCampos *atual = *pCampos, *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->Campo, nomeCampo) == 0)
        {
            if (anterior != NULL)
                anterior->prox = atual->prox;
            else
                *pCampos = atual->prox;

            ApagarDados(atual->Valor);
            atual = NULL;
        }
        else
        {
            anterior = atual;
            atual = atual->prox;
        }
    }
}

// Função para deletar uma tabela de um banco de dados
void ApagarTabela(PTabelas *tabela)
{
    PCampos *atualCampo = tabela->Pcampos, *prox = NULL;
    while (atualCampo != NULL)
    {
        prox = atualCampo;
        DeletarCampo(&atualCampo, atualCampo->Campo);
        atualCampo = prox->prox;
    }
    free(tabela);
}

void DeletarTabela(pontBD *banco, char nomeTabela[])
{
    PTabelas *atualTabela = banco->PTabelas;
    PTabelas *anterior = NULL;

    while (atualTabela != NULL)
    {
        if (strcmp(atualTabela->Tabela, nomeTabela) == 0)
        {
            if (anterior != NULL)
            {
                anterior->prox = atualTabela->prox;
            }
            else
            {
                banco->PTabelas = atualTabela->prox;
            }
            ApagarTabela(atualTabela);
        }

        anterior = atualTabela;
        atualTabela = atualTabela->prox;
    }
}

// Função para deletar um banco de dados
void LiberarBanco(pontBD **banco)
{
    pontBD *aux = *banco;
    PTabelas *atualTabela = (*banco)->PTabelas, *prox = NULL;
    while (atualTabela != NULL)
    {
        prox = atualTabela->prox;
        ApagarTabela(atualTabela);
        atualTabela = prox;
    }
    free(aux);
    *banco = NULL;
}


PTabelas*buscaTab(PTabelas*tab,char nome[])
{
	PTabelas*aux = tab;
	while(aux!=NULL && strcmp(aux->Tabela,nome)!=0)
		aux = aux->prox;
		
		
	if(aux !=NULL)
		return aux;
	else
		return NULL;
}

void pintarFundo(int Cor,int n,int m)
{
	int i,j;
	 textbackground(Cor);
	 for (i = 0; i <n; i++) {
        for (j = 0; j < m; j++) {
            printf(" ");
        }
    }
}

void desenhar(int colunaInicial, int linhaInicial, int colunaFinal, int linhaFinal)
{
    int i, j;
	
	
    for (i = colunaInicial; i <= colunaFinal; i++)
    {
        gotoxy(i, linhaInicial);
        textcolor(BLACK);
        printf("%c", 196);
        gotoxy(i, linhaFinal);
        printf("%c", 196);
    }

 
    for (j = linhaInicial; j <= linhaFinal; j++)
    {
        gotoxy(colunaInicial, j);
        printf("%c", 179); 
        gotoxy(colunaFinal, j);
        printf("%c", 179);
    }

    
    gotoxy(colunaInicial, linhaInicial);
    printf("%c", 218);
    gotoxy(colunaFinal, linhaInicial);
    printf("%c", 191); 
    gotoxy(colunaInicial, linhaFinal);
    printf("%c", 192); 
    gotoxy(colunaFinal, linhaFinal);
    printf("%c", 217); 
}

void selectAll(PTabelas* Tab, char nome[])
{
    clrscr();
    PTabelas* tabela = buscaTab(Tab, nome);
    PCampos* campo = NULL;
    PDados* Dado = NULL;
    int linha = 5, coluna = 3, linhaaux = 0, colunaInicial = 1, linhaInicial = 0, colunaFinal = 0, linhaFinal = 0,linhaInicialTabela=0;

    if (tabela != NULL)
    {
        campo = tabela->Pcampos;
        linhaInicialTabela = linha;

        while (campo != NULL)
        {
        	linha = 5;
            textcolor(BLUE);
            gotoxy(coluna, linha);
            printf("%s", campo->Campo);
			
            Dado = campo->PAtual;
            linha+=3;

            while (Dado != NULL)
            {
                textcolor(LIGHTGREEN);
                gotoxy(coluna, linha);

                if (campo->Tipo == 'I')
                {
                    printf("%d", Dado->UDados.ValorI);
                }
                else if (campo->Tipo == 'N')
                {
                    printf("%.2f", Dado->UDados.ValorN);
                }
                else if (campo->Tipo == 'T')
                {
                    printf("%s", Dado->UDados.ValorT);
                }
                else if (campo->Tipo == 'C')
                {
                    printf("%c", Dado->UDados.ValorC);
                }
                else if (campo->Tipo == 'D')
                {
                    printf("%s", Dado->UDados.ValorD);
                }

                Dado = Dado->prox;
                linha++;
            }

            campo = campo->prox;
            coluna += 20;
        }

        linhaFinal = linha - 1;
        textcolor(BLACK);
        desenhar(colunaInicial, linhaInicialTabela-2, coluna, linhaFinal+2);
        desenhar(colunaInicial+1, linhaInicialTabela-1, coluna-1, linhaInicialTabela+1);
        desenhar(colunaInicial+1, linhaInicialTabela+2, coluna-1, linhaFinal+1);
    }

    getch();
}


void selectBet(PTabelas* Tab, int v1, int v2, char nome[], char campoNome[])
{
    clrscr();
    PTabelas* tabela = buscaTab(Tab, nome);
    PCampos* campo = tabela->Pcampos;
    PDados* Dado, * aux;
    PCampos* campoAux = buscaCampoPorNome(campo, campoNome);
    int linha = 5, coluna = 3, linhaInicialTabela = 0, colunaInicial = 1, linhaFinal = 0, colunaFinal = 0;

    if (tabela != NULL)
    {
        campo = tabela->Pcampos;
        linhaInicialTabela = linha;

        textcolor(YELLOW);
        gotoxy(coluna, linha);
        printf("Tabela: %s", tabela->Tabela);
        linha += 2;

        while (campo != NULL)
        {
            linha = 6;
            gotoxy(coluna, linha);
            textcolor(BLUE);
            printf("%s", campo->Campo);

            Dado = campo->PAtual;
            aux = campoAux->PAtual;
            linha += 2;

            while (Dado != NULL)
            {
                if (aux->UDados.ValorI >= v1 && aux->UDados.ValorI <= v2)
                {
                    gotoxy(coluna, linha);
                    textcolor(LIGHTGREEN);

                    if (campo->Tipo == 'I')
                    {
                        printf("%d", Dado->UDados.ValorI);
                    }
                    else if (campo->Tipo == 'N')
                    {
                        printf("%.2f", Dado->UDados.ValorN);
                    }
                    else if (campo->Tipo == 'T')
                    {
                        printf("%s", Dado->UDados.ValorT);
                    }
                    else if (campo->Tipo == 'C')
                    {
                        printf("%c", Dado->UDados.ValorC);
                    }
                    else if (campo->Tipo == 'D')
                    {
                        printf("%s", Dado->UDados.ValorD);
                    }

                    linha++;
                }

                aux = aux->prox;
                Dado = Dado->prox;
            }

            campo = campo->prox;
            coluna += 20;
        }

        // Calcula a linha final da tabela
        PDados* ultimoDado = campoAux->PAtual;
        while (ultimoDado->prox != NULL)
        {
            ultimoDado = ultimoDado->prox;
        }
        linhaFinal = linha + 1;

        textcolor(BLACK);
        desenhar(colunaInicial, linhaInicialTabela - 2, coluna, linhaFinal + 2);
        desenhar(colunaInicial + 1, linhaInicialTabela - 1, coluna - 1, linhaInicialTabela + 1);
        desenhar(colunaInicial + 1, linhaInicialTabela + 2, coluna - 1, linhaFinal + 1);
    }

    getch();
}


void exibir(pontBD *banco)
{
    clrscr(); 
	int linha = 4, coluna = 2,i=0,j=0,linhaaux=0,colunaInicial = 1, linhaInicial = 0,colunaFinal = 0 ,linhaFinal = 0;
    PTabelas *tabela = banco->PTabelas;
    PCampos *campo = NULL;
    PDados *Dado = NULL;
	
    if (banco == NULL)
    {
    	textcolor(RED);
        printf("## BANCO VAZIO ##");
    }
    else
    {
    	textcolor(GREEN); 
        printf("Banco de Dados: %s\n\n", banco->Banco_Dados);
     
        j = coluna;
        while (tabela)
        {
        	
            gotoxy(coluna, linha);
            linhaInicial = linha-1;
            textcolor(YELLOW); 
            printf("Tabela: %s", tabela->Tabela);
            linha += 2;
			i=linha+1;
            campo = tabela->Pcampos;
            while (campo != NULL)
            {
            
                gotoxy(j, i);
                textcolor(BLUE);                
                printf("%s", campo->Campo);
                Dado = campo->PAtual;
                i++;
                while (Dado != NULL)
                {
                
		        	
		        	textcolor(LIGHTGREEN);
                    gotoxy(j, i);
                    if (campo->Tipo == 'I')
                    {
                        printf("%d", Dado->UDados.ValorI);
                        i++;
                     
                    }
                    else if (campo->Tipo == 'N')
                    {
                        printf("%.2f", Dado->UDados.ValorN);
                        i++;
                   
                    }
                    else if (campo->Tipo == 'T')
                    {
                        printf("%s", Dado->UDados.ValorT);
                        i++;
              
                    }
                    else if (campo->Tipo == 'C')
                    {
                        printf("%c", Dado->UDados.ValorC);
                        i++;
                 
                    }
                
		        	
                    Dado = Dado->prox;
                }	
                if(Dado==NULL)
                {
		        	textcolor(LIGHTGREEN);
					gotoxy(j, i);
					printf("NULL");
					i++;
			  
				}
                if(linhaaux <i)
                	linhaaux = i;
             
                j += 20;
                i = linha+1;
                campo = campo->prox;
            }
         	colunaFinal = j;
            linhaFinal = linhaaux;
            desenhar(colunaInicial,linhaInicial,colunaFinal,linhaFinal);
            linha = linhaaux+2;
         
            j = 2;
            tabela = tabela->prox;
            
        }
    }

    getch();
}
