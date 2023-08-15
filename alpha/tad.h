
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

struct Pdados
{
    union UDados UDados;
    struct Pdados *prox;
};

struct Patual{
    struct Pdados *Pdados;
}; 
typedef struct Patual Patual;

struct PCampos
{
    char Campo[30], Tipo, PK;
    struct Patual *FK;
    struct Pdados *ValorT;
    struct PCampos *Patual, *prox;
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



