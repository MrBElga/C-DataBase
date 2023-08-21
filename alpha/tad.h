union UDados
{
    int ValorI;
    float ValorN;
    char ValorD[11], ValorC;
    char ValorT[21];
};

struct PDados
{
    union UDados UDados;
    struct PDados *prox;
};
typedef struct PDados PDados;

struct PAtual
{
    struct PDados *PDados;
};
typedef struct PAtual PAtual;

struct PCampos
{
    char Campo[30], Tipo, PK;
    struct PAtual *FK;
    struct PDados *ValorT;
    struct PCampos *PAtual, *prox;
};
typedef struct PCampos PCampos;

struct PTabelas
{
    char Tabela[30];
    struct PCampos *Patual;
    struct PTabelas *prox, *ant;
};
typedef struct PTabelas PTabelas;

struct pontBD
{
    char Banco_Dados[50];
    struct PTabelas *PTabelas;
};
typedef struct pontBD pontBD;

PDados *novaCaixaDados()
{
    PDados *nova = (PDados *)malloc(sizeof(PDados));
    nova->UDados.ValorI = 0;
    nova->UDados.ValorN = 0.0;
    nova->UDados.ValorC = '\0';
    nova->UDados.ValorD[0] = '\0';
    nova->UDados.ValorT[0] = '\0';
    nova->prox = NULL;
    return nova;
}



void CadastrarDados(PCampos *pCampos, union UDados nDado)
{
    PCampos *atualCampo = pCampos;
    while (atualCampo != NULL && atualCampo->ValorT != NULL) {
        atualCampo = atualCampo->prox;
    }
    
    if (atualCampo != NULL) {
        atualCampo->ValorT = novaCaixaDados();
        atualCampo->ValorT->UDados = nDado;
    }
}



PCampos *novoCaixaCampo(char nome[], char Tipo, char FK)
{
    PCampos *nova = (PCampos *)malloc(sizeof(PCampos));
    nova->prox = NULL; 
	nova->FK = NULL;
	nova->PAtual = NULL;
	nova->ValorT = NULL;
    nova->Tipo = Tipo;
    nova->PK = FK;
    strcpy(nova->Campo, nome);
    return nova;
}

void CadastrarCampos(PCampos **pCampos, char nome[], char Tipo, char FK)
{
    PCampos *novo = novoCaixaCampo(nome, Tipo, FK);
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

PTabelas *novaTabela(char nome[])
{
    PTabelas *nova = (PTabelas *)malloc(sizeof(PTabelas));
    strcpy(nova->Tabela, nome);
    nova->Patual = NULL;
    nova->prox = nova->ant = NULL;
    return nova;
}

void CadastrarTabela(PTabelas **Tabela, char nome[])
{
    PTabelas *nova = novaTabela(nome);
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


void ExibirDados(PCampos *pCampos)
{
    PCampos *atualCampo = pCampos;
    while (atualCampo != NULL)
    {
        printf("Campo: %s\n", atualCampo->Campo);
        printf("Tipo: %c\n", atualCampo->Tipo);

        // Verificar o tipo do dado e exibir o valor correspondente
        if (atualCampo->ValorT != NULL) {
            PDados *dados = atualCampo->ValorT;
            if (atualCampo->Tipo == 'I') {
                printf("Valor: %d\n", dados->UDados.ValorI);
            }
            else if (atualCampo->Tipo == 'N') {
                printf("Valor: %.2f\n", dados->UDados.ValorN);
            }
            else if (atualCampo->Tipo == 'T') {
                printf("Valor: %s\n", dados->UDados.ValorT);
            }
            else if (atualCampo->Tipo == 'C') {
                printf("Valor: %c\n", dados->UDados.ValorC);
            }
        }

        printf("\n");

        atualCampo = atualCampo->prox;
    }
}





void ExibirCampos(PCampos *pCampos)
{
    PCampos *atual = pCampos;
    while (atual != NULL)
    {
        printf("Campo: %s\n", atual->Campo);
        printf("Tipo: %c\n", atual->Tipo);
        printf("PK: %c\n\n", atual->PK);

        atual = atual->prox;
    }
}
