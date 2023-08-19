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

struct PAtual{
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

void iniciarNovaCaixa( PDados *)

Pdados *novaCaixaDados( PDados *nova ) 
{   
  
    
    

    return *nova;
}

void CadastrarDados( PDados **pDados, UDados Dados )
{
    PDados *nova = (PDados*)malloc(sizeof(PDados));
    nova = NULL;
    nova = novaCaixaDados(nova);

}