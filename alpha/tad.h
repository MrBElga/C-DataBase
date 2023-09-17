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

struct PCampos
{
    char Campo[30], Tipo, PK;
    struct PDados *ValorT, *PAtual;
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
    CadastrarDados(&(campos->ValorT), Tipo, nDado);
    if (campos->ValorT->prox == NULL)
        campos->PAtual = campos->ValorT;
}

// Alterar
// Dados
void AlterarDado(PDados *pDados, char NovoDado[])
{
    strcpy(pDados->UDados.ValorT, NovoDado);
}

// Campos
void AlterarCampo(PCampos *pCampos, char NovoCampo[])
{
    strcpy(pCampos->Campo, NovoCampo);
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

// Deletar linha

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

    return 1;
}

void excluirMesmoIndiceOutrosCampos(PCampos *campos, PCampos *campoAtual, PDados *indiceAtual)
{
    PCampos *atualCampo = campos;

    while (atualCampo != NULL)
    {
        if (atualCampo != campoAtual)
        {
            PDados *anterior = NULL, *atual = atualCampo->ValorT;
            while (atual != NULL)
            {
                if (atual == indiceAtual)
                {
                    if (anterior != NULL)
                    {
                        anterior->prox = atual->prox;
                        free(atual);
                    }
                    else
                    {
                        atualCampo->ValorT = atual->prox;
                        free(atual);
                    }
                    break;
                }
                anterior = atual;
                atual = atual->prox;
            }
        }
        atualCampo = atualCampo->prox;
    }
}

void DeletarLinha(pontBD **banco, char nomeTabela[], char nomeCampo[], union UDados nDado)
{
    PTabelas *aux = buscaTabelaPorNome(*banco, nomeTabela);
    PCampos *campo;
    int posicaoDado = -1, pos = -1;
    PDados *atual;
    PCampos *atualCampo;
    PDados *anterior;

    if (aux == NULL)
    {
        printf("Tabela %s nao encontrada.\n", nomeTabela);
    }
    else
    {

        campo = buscaCampoPorNome(aux->Pcampos, nomeCampo);

        if (campo == NULL)
        {
            printf("Campo %s nao encontrado na tabela %s.\n", nomeCampo, nomeTabela);
        }
        else
        {

            atual = campo->ValorT;
            anterior = NULL;

            while (atual != NULL)
            {
                if (compararDados(atual->UDados, nDado, campo->Tipo))
                {
                    if (anterior != NULL)
                    {
                        anterior->prox = atual->prox;
                        free(atual);
                        atual = anterior->prox;
                    }
                    else
                    {
                        campo->ValorT = atual->prox;
                        free(atual);
                        atual = campo->ValorT;
                    }
                    posicaoDado = 0;
                }
                else
                {
                    anterior = atual;
                    atual = atual->prox;
                    posicaoDado++;
                }
            }
            if (posicaoDado != -1)
            {
                atualCampo = aux->Pcampos;

                while (atualCampo != NULL)
                {
                    atual = atualCampo->ValorT;
                    anterior = NULL;

                    pos = 0;
                    while (pos < posicaoDado && atual != NULL)
                    {
                        anterior = atual;
                        atual = atual->prox;
                        pos++;
                    }

                    if (atual != NULL)
                    {
                        if (anterior != NULL)
                        {
                            anterior->prox = atual->prox;
                            free(atual);
                        }
                        else
                        {
                            atualCampo->ValorT = atual->prox;
                            free(atual);
                        }
                    }

                    atualCampo = atualCampo->prox;
                }
            }
            else
            {
                printf("Registro nao encontrado no campo %s.\n", nomeCampo);
            }
        }
    }
}

// Campos
void DeletarCampo()
{
}
// Tabelas
void DeletarTabela()
{
}
// Banco
void DeletarBanco()
{
}

// exibe os dados
void ExibirDados(PCampos *pCampos)
{
    PCampos *atualCampo = pCampos;
    PDados *dados = NULL;
    while (atualCampo != NULL)
    {
        printf("Campo: %s\n", atualCampo->Campo);
        printf("Tipo: %c\n", atualCampo->Tipo);
        if (atualCampo->ValorT != NULL)
        {
            dados = atualCampo->ValorT;
            while (dados != NULL)
            {
                if (atualCampo->Tipo == 'I')
                {
                    printf("Valor: %d\n", dados->UDados.ValorI);
                }
                else if (atualCampo->Tipo == 'N')
                {
                    printf("Valor: %.2f\n", dados->UDados.ValorN);
                }
                else if (atualCampo->Tipo == 'T')
                {
                    printf("Valor: %s\n", dados->UDados.ValorT);
                }
                else if (atualCampo->Tipo == 'C')
                {
                    printf("Valor: %c\n", dados->UDados.ValorC);
                }
                dados = dados->prox;
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
        printf("%s \t", atual->Campo);
        atual = atual->prox;
    }
    printf("\n");
}

void ExibirCampo(PCampos *pCampos, char Nome[])
{
    PCampos *atual = pCampos;
    while (atual != NULL)
    {
        if (strcmp(atual->Campo, Nome) == 0)
            printf("Campo: %s", atual->Campo);
        atual = atual->prox;
    }
    printf("\n");
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
        ExibirCampos(tabelaAlvo->Pcampos);
        // ExibirCamposTabela();
        ExibirDados(tabelaAlvo->Pcampos);
        // ExibirDadosTabela();
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

void ExibirLinha(PCampos **pCampos)
{
    char flag = '1';
    union UDados Dados;
    PCampos *atualCampo = *pCampos;

    ExibirCampos(*pCampos);

    while (flag == '1')
    {
        while (atualCampo != NULL)
        {
            flag = '0';
            if (atualCampo->PAtual != NULL)
            {
                flag = '1';

                Dados = atualCampo->PAtual->UDados;

                if (atualCampo->Tipo == 'I')
                {
                    printf("%d \t", Dados.ValorI);
                }
                else if (atualCampo->Tipo == 'N')
                {
                    printf("%.2f \t", Dados.ValorN);
                }
                else if (atualCampo->Tipo == 'T')
                {
                    printf("%s \t", Dados.ValorT);
                }
                else if (atualCampo->Tipo == 'C')
                {
                    printf("%c \t", Dados.ValorC);
                }

                atualCampo->PAtual = atualCampo->PAtual->prox;
            }
            atualCampo = atualCampo->prox;
        }
        atualCampo = *pCampos;
        printf("\n");
    }
    atualCampo = *pCampos;
    while (atualCampo != NULL)
    {
        atualCampo->PAtual = atualCampo->ValorT;
        atualCampo = atualCampo->prox;
    }
}
