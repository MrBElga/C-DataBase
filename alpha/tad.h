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



//Buscas 

//Dados
PDados *BuscaDados(PDados *pDados, union UDados nDado)
{
    PDados *aux = pDados;
    while (aux != NULL)
    {
        if ((aux->UDados.ValorI == nDado.ValorI) || (aux->UDados.ValorN == nDado.ValorN) || (strcmp(aux->UDados.ValorD, nDado.ValorD) == 0) || (aux->UDados.ValorC == nDado.ValorC) || (strcmp(aux->UDados.ValorT, nDado.ValorT) == 0))
        {
            return aux; 
        }
        aux = aux->prox;
    }
    return NULL;
}


//Campos
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

//Tabelas
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
//Banco
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

//FK



// Cadastros

// cadastra os dados do banco [OK]
PDados *novaCaixaDados(union UDados nDado)
{
    PDados *nova = (PDados *)malloc(sizeof(PDados));
    nova->UDados = nDado;
    nova->prox = NULL;
    return nova;
}

void CadastrarDados(PDados **pDados, char tipo, union UDados nDado)
{
    PDados *novaCaixa = novaCaixaDados(nDado);

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
    nova->ValorT = NULL;
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

// Cadastrar Banco [OK]
pontBD *NovoCaixaBanco(char nome[])
{
    pontBD *novo = (pontBD *)malloc(sizeof(pontBD));
    strcpy(novo->Banco_Dados, nome);
    novo->PTabelas = NULL;
    return novo;
}

void CadastrarBannco(pontBD **Banco, char nome[])
{
    pontBD *novo = NovoCaixaBanco(nome)/* ,*temp = *Banco */;

    if (*Banco == NULL)
    {
        *Banco = novo;
    }
    else
    {
        printf("no momento só é possivel cadastrar um banco de dados\n");
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
        CadastrarCampos(&(tabelaAlvo->Patual), nomeCampo, Tipo, FK);
    }
}

// Função para cadastrar dados em um campo de uma tabela
void CadastrarDadosNaTabela(PCampos *campos, char tipo, union UDados nDado)
{
    CadastrarDados(&(campos->ValorT), tipo, nDado);
}



//Alterar

//Dados
//Campos
//Tabelas
//Banco

//Deletar

//Dados
//Campos
//Tabelas
//Banco

// exibe os dados
void ExibirDados(PCampos *pCampos)
{
    PCampos *atualCampo = pCampos;
    while (atualCampo != NULL)
    {
        printf("Campo: %s\n", atualCampo->Campo);
        printf("Tipo: %c\n", atualCampo->Tipo);
        if (atualCampo->ValorT != NULL)
        {
            PDados *dados = atualCampo->ValorT;
      
            if (atualCampo->Tipo == 'I')
            {
                      printf("I");
                printf("Valor: %d\n", dados->UDados.ValorI);
            }
            else if (atualCampo->Tipo == 'N')
            {
                      printf("N");
                printf("Valor: %.2f\n", dados->UDados.ValorN);
            }
            else if (atualCampo->Tipo == 'T')
            {
                      printf("T");
                printf("Valor: %s\n", dados->UDados.ValorT);
            }
            else if (atualCampo->Tipo == 'C')
            {
                      printf("C");
                printf("Valor: %c\n", dados->UDados.ValorC);
            }
        }
        printf("\n");
        atualCampo = atualCampo->prox;
    }
}

// exibe os campos
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

// Função para exibir campos e dados de uma tabela específica
void ExibirTabela(PTabelas *tabelas, char nomeTabela[])
{
    PTabelas *tabelaAlvo = tabelas;
    while (tabelaAlvo != NULL && strcmp(tabelaAlvo->Tabela, nomeTabela) != 0)
    {
        tabelaAlvo = tabelaAlvo->prox;
    }

    if (tabelaAlvo != NULL)
    {
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