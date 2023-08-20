// Union data type
// I INTEGER
// N NUMERIC
// D DATE (aaaa-mm-dd)
// C CHARACTER(1)
// T CHARACTER(20)

union UDados
{
    int ValorI;
    float ValorN;
    char valorD[11], ValorC, ValorT[21];
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
    struct Pdados *ValorT;
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
    struct pontBD *PTabelas;
};
typedef struct pontBD pontBD;


//cadastro Dados
Pdados *novaCaixaDados()
{
    PDados *nova = (PDados*)malloc(sizeof(PDados));
    nova->prox = NULL;
    return nova;
}

void CadastrarDados(PDados **pDados, union UDados nDado)
{
    PDados *novo = novaCaixaDados();
    novo->Udados = nDado;

    if (*pDados == NULL)
    {
        *pDados = novo;
    }
    else
    {
        //deve inserir no final não no incio
        novo->prox = *pDados;
        *pDados = novo;
    }
}

//Excluir Dados

//Exibir Dados

//Cadastrar Campos
pCampos *novoCaixaCampo(char nome[], char Tipo,char FK)
{
    PCampos *nova =(PCampos*)malloc(sizeof(PCampos));
    nova -> prox =  nova -> FK =  nova -> PAtual =   nova -> PDados =NULL;
    novo -> Tipo = Tipo;
    novo -> FK = FK;
    strcpy(novo -> Campo, nome);
    return(nova);
}

void CadastrarCampos(PCampos **PCampos,char nome[], char Tipo,char FK)
{
    PCampos *novo = novoCaixaCampo(nome,Tipo, FK);
    if(*PCampos == NULL)
    {
        *PCampos = novo;
    }
    else
    {

    }
}

//Cadastro Tabelas
void CadastrarTabela()
{

}