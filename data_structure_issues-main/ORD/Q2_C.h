#include <stdio.h>//responsável por printf
#include <stdlib.h> //responsável por malloc, free...
#include <locale.h> //serve para exibir acento.
#define M 20 // tamanho da tabela




typedef struct { //dados das pessoas
    int matricula;
    char nome[50];
} Pessoa;

// nó usado na lista encadeada
typedef struct no {
    Pessoa pessoa;
    struct no *proximo;
} No;

// Lista com um ponteiro para o primeiro nó
typedef struct {
    No *inicio;
    int tam;
} Lista;

// Tabela
Lista *tabela[M];


// Recebe os dados e retorna
Pessoa criarPessoa() {
    setlocale(LC_ALL, "Portuguese"); //Consegue exibir os acentos nos printf.

    Pessoa p;
    printf("\nDigite o nome: ");
    scanf("%*c");
    fgets(p.nome, 50, stdin);
    printf("\nDigite a matricula: ");
    scanf("%d", &p.matricula);
    return p;
}

// --------------Funções -----------//

// Responsável por exibir
void imprimirPessoa(Pessoa p) {
      printf("\tNome: %s\tMatricula: %d\n", p.nome, p.matricula);
}

// Cria uma lista vazia e retorna seu endereço
Lista* criarLista() {
    Lista *l = malloc(sizeof(Lista));
    l->inicio = NULL;
    l->tam = 0;
    return l;
}


void inserirInicio(Pessoa p, Lista *lista) {
    No *no = malloc(sizeof(No));
    no->pessoa = p;
    no->proximo = lista->inicio;
    lista->inicio = no;
    lista->tam++;
}

// Busca um elemento na lista
No* buscarNo(int mat, No *inicio) {

    while(inicio != NULL) {
        if(inicio->pessoa.matricula == mat)
            return inicio;
        else
            inicio = inicio->proximo;
    }
    return NULL;// matricula não encontrada
}

void imprimirLista(No *inicio) {
    while(inicio != NULL) {
        imprimirPessoa(inicio->pessoa);
        inicio = inicio->proximo;
    }
}

// Inicializa a tabela com uma lista vazia em cada posição.
void inicializar(){
    int i;
    for(i = 0; i < M; i++)
        tabela[i] = criarLista();
}


// Função de espalhamento
int funcaoEspalhamento(int mat){ //também conhecido como hash
    return mat % M;
}

// Cria e insere na tabela
void inserTabela(){
    Pessoa pes = criarPessoa();
    int indice = funcaoEspalhamento(pes.matricula);
    inserirInicio(pes, tabela[indice]);
}

// Busca uma pessoa. Seu retorno é um endereço ou NULL.
Pessoa* buscarPessoaTabela(int mat){
    int indice = funcaoEspalhamento(mat);
    No *no = buscarNo(mat, tabela[indice]->inicio);
    if(no)
        return &no->pessoa;
    else
        return NULL;
}

// Imprime a tabela
void imprimirTabela(){
    setlocale(LC_ALL, "Portuguese"); //Consegue exibir os acentos nos printf.

    int i;
    printf("\n---------------------TABELA-------------------------\n");
    for(i = 0; i < M; i++){
        printf("%d Lista, tamanho: %d\n", i, tabela[i]->tam);
        imprimirLista(tabela[i]->inicio);
    }
    printf("-----------------------TABELA-----------------------\n");
}
