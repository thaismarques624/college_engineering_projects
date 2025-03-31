#ifndef avl_h
#define avl_h

#ifdef __cplusplus
exterm "C" {
#endif

typedef struct no_avl{
     struct no_avl *pai;
     struct no_avl *esq;
     struct no_avl *dir;
     void *info; //guarda a informa��o
     int balan; //fator de balanceamento
} no_avl;

typedef struct avl_arv{
     no_avl *root;            // Raiz da �rvore
     unsigned int num_nodes;    // N�mero de n�s da �rvore

     // Fun��o que compara duas informa��es
     int (*compara_info)( const void *, const void * );
     // Fun��o que imprime uma informa��o
     void (*imprime_info)( const void * );

} avl_arv;

/* Fun��es para manipula��o da �rvore */

// Inicializa��o da �rvore
void avl_init ( avl_arv **, int (*compara_info)( const void *, const void * ),
        void (*imprime_info)( const void * ));

// Insere um elemento na �rvore
int avl_insert (avl_arv **, no_avl *, no_avl **, void * );

// Remove um elemento da �rvore
int avl_remove ( avl_arv **, no_avl **, void * );

// Realiza o percurso em pr�-ordem
void avl_walk_pre ( avl_arv *, no_avl * );

// Realiza o percurso em pos-ordem
void avl_walk_pos ( avl_arv *, no_avl * );

// Realiza o percurso em ordem simetrica
void avl_walk_sim ( avl_arv *, no_avl * );

// Realiza o percurso na �rvore por n�vel
void avl_walk_byLevel ( avl_arv * );

// Faz uma busca na �rvore
no_avl *avl_search ( avl_arv *, no_avl *, void * );

// Retorna a altura de uma sub-�rvore
int avl_height ( no_avl* );

#ifdef __cplusplus
}
#endif


#endif
