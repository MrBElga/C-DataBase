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


void CadastrarDados(PDados **pDados, union UDados nDado)
{
    PDados *novo = novaCaixaDados();
    novo->UDados = nDado;

    if (*pDados == NULL)
    {
        *pDados = novo;
    }
    else
    {
        PDados *temp = *pDados;
        while (temp->prox != NULL)
        {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}

PCampos *novoCaixaCampo(char nome[], char Tipo, char FK)
{
    PCampos *nova = (PCampos *)malloc(sizeof(PCampos));
    nova->prox = nova->FK = nova->PAtual = nova->ValorT = NULL;
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



void ExibirDados(PDados *pDados)
{
    PDados *atual = pDados;
    while (atual != NULL)
    {
        printf("Tipo do dado: ");

        if (atual->UDados.ValorI > 0) {
            printf("INTEGER\n");
            printf("Valor: %d\n", atual->UDados.ValorI);
        }
        else if (atual->UDados.ValorN > 0) {
            printf("NUMERIC\n");
            printf("Valor: %.2f\n", atual->UDados.ValorN);
        }
        else if (strlen(atual->UDados.ValorD) > 0) {
            printf("DATE\n");
            printf("Valor: %s\n", atual->UDados.ValorD);
        }
        else if (atual->UDados.ValorC != '\0') {
            printf("CHARACTER\n");
            printf("Valor: %c\n", atual->UDados.ValorC);
        }
        else if (strlen(atual->UDados.ValorT) > 0) {
            printf("CHARACTER (20)\n");
            printf("Valor: %s\n", atual->UDados.ValorT);
        }
        else {
            printf("NULO\n");
        }

        printf("\n");

        atual = atual->prox;
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
