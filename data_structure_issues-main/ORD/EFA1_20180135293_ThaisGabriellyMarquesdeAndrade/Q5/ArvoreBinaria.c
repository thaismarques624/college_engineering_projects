/* Implementa��o de �rvore bin�ria */

#include <stdio.h>
#include <stdlib.h>

//armazenando as informa��es
typedef struct arv
{
  struct arv* sad;
  struct arv* sae;
  int num;
} ARV;/* A estrutura � representada por um ponteiro
        para o n� raiz. Assim vamos ter acesso aos outros n�s.*/


ARV* c_arv(){ //criando arvore.
   return NULL;
}

int arv_v(ARV* t){ //verificando se a arvore est� vazia
   return t == NULL;
}

void inf_arv(ARV* t){ //puxando a informa��o da arvore

    printf("<"); //para organizar, menor significa esquerda

    if(!arv_v(t)){ //se a arvore n�o estiver vazia

    // Mostra os elementos em pr�-ordem
    printf("%d ", t->num); //mostra a raiz
    inf_arv(t->sae); // mostra a sub�rvore � esquerda
    inf_arv(t->sad); //mostra a sub�rvore � direita
  }
   printf(">"); // para organizar, maior significa direita - dica sugerida para organizar.
}

void inser_avr(ARV** t, int num) // fun��o que insere dados na �rvore.
{
  if(*t == NULL)
  {
    *t = (ARV*)malloc(sizeof(ARV)); //Aloca mem�ria
    (*t)->sae = NULL;
    (*t)->sad = NULL;
    (*t)->num = num; //Armazena a informa��o
  } else {
    if(num < (*t)->num) //Se o n�mero for menor ent�o vai para a sub-esquerda
    {
      inser_avr(&(*t)->sae, num);
    }
    if(num > (*t)->num) //Se o n�mero for maior ent�o vai para a sub_direita
    {
      inser_avr(&(*t)->sad, num);
    }
  }
}

int verf_arv(ARV* t, int num) { //verifica se determinado elemento pertence a �rvore.

  if(arv_v(t)) {
    return 0;
  }
  return t->num==num ||verf_arv(t->sae, num) || verf_arv(t->sad, num); //interrompe quando o elemento � encontrado.
}

int main()
{
 ARV* t = c_arv(); //criando a �rvore

   //inserindo elementos
   inser_avr(&t, 20);
   inser_avr(&t, 15);
   inser_avr(&t, 12);
   inser_avr(&t, 103);

   inf_arv(t); // mostrando os elementos em pr�-ordem.

   printf("\n\nInfor.:" );
  if(arv_v(t)){//verifica��o, se a arvore est� vazia ou n�o.
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

  //Faltou o desenvolvimento da fun��o remover.

  return 0;
}
