/* Implementação de árvore binária */

#include <stdio.h>
#include <stdlib.h>

//armazenando as informações
typedef struct arv
{
  struct arv* sad;
  struct arv* sae;
  int num;
} ARV;/* A estrutura é representada por um ponteiro
        para o nó raiz. Assim vamos ter acesso aos outros nós.*/


ARV* c_arv(){ //criando arvore.
   return NULL;
}

int arv_v(ARV* t){ //verificando se a arvore está vazia
   return t == NULL;
}

void inf_arv(ARV* t){ //puxando a informação da arvore

    printf("<"); //para organizar, menor significa esquerda

    if(!arv_v(t)){ //se a arvore não estiver vazia

    // Mostra os elementos em pré-ordem
    printf("%d ", t->num); //mostra a raiz
    inf_arv(t->sae); // mostra a subárvore à esquerda
    inf_arv(t->sad); //mostra a subárvore à direita
  }
   printf(">"); // para organizar, maior significa direita - dica sugerida para organizar.
}

void inser_avr(ARV** t, int num) // função que insere dados na árvore.
{
  if(*t == NULL)
  {
    *t = (ARV*)malloc(sizeof(ARV)); //Aloca memória
    (*t)->sae = NULL;
    (*t)->sad = NULL;
    (*t)->num = num; //Armazena a informação
  } else {
    if(num < (*t)->num) //Se o número for menor então vai para a sub-esquerda
    {
      inser_avr(&(*t)->sae, num);
    }
    if(num > (*t)->num) //Se o número for maior então vai para a sub_direita
    {
      inser_avr(&(*t)->sad, num);
    }
  }
}

int verf_arv(ARV* t, int num) { //verifica se determinado elemento pertence a árvore.

  if(arv_v(t)) {
    return 0;
  }
  return t->num==num ||verf_arv(t->sae, num) || verf_arv(t->sad, num); //interrompe quando o elemento é encontrado.
}

int main()
{
 ARV* t = c_arv(); //criando a árvore

   //inserindo elementos
   inser_avr(&t, 20);
   inser_avr(&t, 15);
   inser_avr(&t, 12);
   inser_avr(&t, 103);

   inf_arv(t); // mostrando os elementos em pré-ordem.

   printf("\n\nInfor.:" );
  if(arv_v(t)){//verificação, se a arvore está vazia ou não.
    printf("\nArvore esta vazia\n");

  } else {
    printf("\n\nArvore nao esta vazia\n");
  }

  //testes para verificar se os elementos pertence a arvore
  if(verf_arv(t, 10)) {
    printf("\nEsse 10 pertence a arvore\n");
  } else {
     printf("\nEsse 10 nao pertence a arvore\n");
  }

  if(verf_arv(t, 103)){
     printf("\nEsse 103 pertence a arvore\n");
  } else {
     printf("\nEsse 103 nao pertence a arvore\n");
  }

  //Faltou o desenvolvimento da função remover.

  return 0;
}
