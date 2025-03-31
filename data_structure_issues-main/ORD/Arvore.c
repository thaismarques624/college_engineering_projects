/*TDA ARVORE BINARIA
   *Todas as operações
*/

#include <stdio.h>
#include <stdlib.h>

/*Montando o struct*/

struct no{
    int num;
    struct no *dir;
    struct no *esq;


};
typedef struct no no; //cria um sinônimo para tipos de dados existentes.

void c_Arvore(no **raiz){  //Criando a arvore
    *raiz = NULL;
}

void inser(no **raiz, int num2){ //função para inserir nós
    if(*raiz == NULL){ //Checando a raiz
        *raiz = (no *)malloc(sizeof(no));
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        (*raiz)->num = num2;
    }else{
        if(num2 < ((*raiz)->num)){
            inser(&((*raiz)->esq), num2);
        }else{
            inser(&((*raiz)->dir), num2);
        }
    }

}

// Remoção começa aqui

no *MaiorDireita(no **No)
{
    if((*No)->dir != NULL)
    {
       return MaiorDireita(&(*No)->dir);
    }
    else
    {
       no *aux = *No;

       if((*No)->esq != NULL) // verificação para que o nó não perca os filhos.
        {
          *No = (*No)->esq;
        }
        else
        {
            *No = NULL;
            return aux;
        }
    }

}

no *MenorEsquerda(no **No)
{
    if((*No)->esq != NULL)
    {
       return MenorEsquerda(&(*No)->esq);
    }
    else
    {
        no *aux = *No;
        if((*No)->dir!= NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da direita!
        {
          *No = (*No)->dir;
        }
        else
        {
          *No = NULL;
        }
        return aux;
    }
}

void remover(no **raiz, int num){
    if(*raiz == NULL){   // verifica se o numero existe na arvore
       printf("Esse numero não existe na arvore");
       getch();
       return;
    }
    if(num < (*raiz)->num)
       remover(&(*raiz)->esq, num);
     else
       if(num > (*raiz)->num)
          remover(&(*raiz)->dir, num);

       else{    //aqui é quando acha o numero

          no *pAux = *raiz;

          if (((*raiz)->esq == NULL) && ((*raiz)->dir == NULL)){         // se nao houver filhos...
                free(pAux);
                (*raiz) = NULL;
               }

          else{     // se sobrar só o filho da direita
             if ((*raiz)->esq == NULL){
                (*raiz) = (*raiz)->dir;
                pAux->dir = NULL;
                free(pAux); pAux = NULL;
                }
             else{ //se sobrar só o filho da esquerda
                if ((*raiz)->dir == NULL){
                    (*raiz) = (*raiz)->esq;
                    pAux->esq = NULL;
                    free(pAux); pAux = NULL;
                    }
                else{
                   pAux = MaiorDireita(&(*raiz)->esq);
                   pAux->esq = (*raiz)->esq;
                   pAux->dir = (*raiz)->dir;
                   (*raiz)->esq = (*raiz)->dir = NULL;
                   free((*raiz));  *raiz = pAux;  pAux = NULL;
                   }
                }
             }
          }
}

void PreOrdem(no *raiz){ // percorre a esquerda, percorre a direita
    if(raiz != NULL){
        printf("\n%d", raiz->num);
        PreOrdem(raiz->esq);
        PreOrdem(raiz->dir);
    }
}

void EmOrdem(no *raiz){ //percorre esquerda, percorre direita
    if(raiz != NULL){
        EmOrdem(raiz->esq);
        printf("\n%d", raiz->num);
        EmOrdem(raiz->dir);
    }
}
void PosOrdem(no *raiz){
    if(raiz != NULL){
        PosOrdem(raiz->esq);
        PosOrdem(raiz->dir);
        printf("\n%d", raiz->num);
    }
}
int main(){

        //no* No =  c_Arvore(); // criando a arvore
        inser(&no,12);
        inser(&no,15);
        inser(&no,10);

        EmOrdem(no);



}
