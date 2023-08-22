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

PDados *novaCaixaDados(union UDados nDado)
{
    PDados *nova = (PDados *)malloc(sizeof(PDados));
    nova->UDados = nDado;
    nova->prox = NULL;
    return nova;
}


void CadastrarDados(PDados **pDados, union UDados nDado)
{
    PDados *novaCaixa = novaCaixaDados(nDado);

    if (*pDados != NULL) {
        PDados *ultimo = *pDados;
        while (ultimo->prox != NULL) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novaCaixa;
    } else {
        *pDados = novaCaixa;
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

PTabelas *novaCaixaTabela(char nome[])
{
    PTabelas *nova = (PTabelas *)malloc(sizeof(PTabelas));
    strcpy(nova->Tabela, nome);
    nova->Patual = NULL;
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


//Cadastrar Banco´
pontBD *NovoCaixaBanco(char nome[])
{
    pontBD *novo = (pontBD *)malloc(sizeof(pontBD));
    strcpy(novo->Banco_Dados, nome);
    novo->PTabelas = NULL;
    return novo;
}

void CadastrarBannco(pontBD **Banco, char nome[])
{
    pontBD *novo = NovoCaixaBanco(nome), *temp = *Banco;

    if (*Banco == NULL)
    {
        *Banco = novo;
    }
    else
    {
       
        printf("delete o banco atual para cadastrar um novo");
        getchar();
    }
}

void ExibirDados(PCampos *pCampos)
{
    PCampos *atualCampo = pCampos;
    while (atualCampo != NULL)
    {
        printf("Campo: %s\n", atualCampo->Campo);
        printf("Tipo: %c\n", atualCampo->Tipo);
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

// Função para exibir todos os bancos
void ExibirBancos(pontBD *bancos)
{
    pontBD *atualBanco = bancos;
    printf("Banco: %s\n", atualBanco->Banco_Dados);
    
    
}

// Função para exibir todas as tabelas de um banco
void ExibirTabelas(PTabelas *tabelas)
{
    PTabelas *atualTabela = tabelas;
    while (atualTabela != NULL)
    {
        printf("Tabela: %s\n", atualTabela->Tabela);
        atualTabela = atualTabela->prox;
    }
}

// Função para exibir campos de uma tabela
void ExibirCamposTabela(PCampos *campos)
{
    ExibirCampos(campos);
}

// Função para exibir todos os dados de uma tabela
void ExibirDadosTabela(PCampos *campos)
{
    ExibirDados(campos);
}

// Função para cadastrar um novo campo em uma tabela
void CadastrarCampoNaTabela(PTabelas **Tabela, char nomeTabela[], char nomeCampo[], char Tipo, char FK)
{
    PTabelas *tabelaAlvo = *Tabela;
    while (tabelaAlvo != NULL && strcmp(tabelaAlvo->Tabela, nomeTabela) != 0) {
        tabelaAlvo = tabelaAlvo->prox;
    }

    if (tabelaAlvo != NULL) {
        CadastrarCampos(&(tabelaAlvo->Patual), nomeCampo, Tipo, FK);
    }
}

// Função para cadastrar dados em um campo de uma tabela
void CadastrarDadosNaTabela(PCampos *campos, union UDados nDado)
{
    CadastrarDados(&(campos->ValorT), nDado);
}

// Função para exibir campos e dados de uma tabela específica
void ExibirTabela(PTabelas *tabelas, char nomeTabela[])
{
    PTabelas *tabelaAlvo = tabelas;
    while (tabelaAlvo != NULL && strcmp(tabelaAlvo->Tabela, nomeTabela) != 0) {
        tabelaAlvo = tabelaAlvo->prox;
    }

    if (tabelaAlvo != NULL) {
        printf("Tabela: %s\n", tabelaAlvo->Tabela);
        ExibirCamposTabela(tabelaAlvo->Patual);
        ExibirDadosTabela(tabelaAlvo->Patual);
    }
}

// Função para exibir todos os detalhes das tabelas
void ExibirTodasAsTabelas(pontBD *bancos)
{
    pontBD *atualBanco = bancos;
    PTabelas *atualTabela = atualBanco->PTabelas;
  
        printf("Banco: %s\n", atualBanco->Banco_Dados);
      
        while (atualTabela != NULL)
        {
            ExibirTabela(bancos->PTabelas, atualTabela->Tabela);
            atualTabela = atualTabela->prox;
        }
   
}
