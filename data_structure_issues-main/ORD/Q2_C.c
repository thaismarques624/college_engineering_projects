/* -----Nome: Tha�s Gabrielly Marques
--------Quest�o 2- C)*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //serve para exibir acento.
#include "Q2_C.h"

int main() {
    setlocale(LC_ALL, "Portuguese"); //Consegue exibir os acentos nos printf.
    int op, mat;
    Pessoa *p;

    inicializar();

    do {
        printf("\n\tBanco de dados dos Funcion�rios, escolha uma op��o:\n");
        printf("\n1 - Imprimir tabela\n2 - Inserir\n3 - Buscar\n0 - Sair\n");
        printf("\nOp��o: ");
        scanf("%d", &op);

        switch(op){
        case 1:
            imprimirTabela();
            break;
        case 2:
            inserTabela();
            break;
        case 3:
            printf("Qual a matricula a ser buscada? ");
            scanf("%d", &mat);
            p = buscarPessoaTabela(mat);
            if(p) {
                printf("\nPessoa encontrada:\n Matr�cula: %d\tNome: %s", p->matricula, p->nome);
            } else
                printf("\nMatr�cula n�o encontrada, tente novamente!\n");
            break;
        case 0:
            printf("\nAt� logo...\n");
            break;

        default:
            printf("\nOp��o invalida, tente novamente!\n");
        }
    } while(op != 0);

    return 0 ;
}
