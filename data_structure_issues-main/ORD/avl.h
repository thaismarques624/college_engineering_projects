#ifndef avl_h
#define avl_h

#ifdef __cplusplus
exterm "C" {
#endif

typedef struct no_avl{
     struct no_avl *pai;
     struct no_avl *esq;
     struct no_avl *dir;
     void *info; //guarda a informação
     int balan; //fator de balanceamento
} no_avl;

typedef struct avl_arv{
     no_avl *root;            // Raiz da árvore
     unsigned int num_nodes;    // Número de nós da árvore

     // Função que compara duas informações
     int (*compara_info)( const void *, const void * );
     // Função que imprime uma informação
     void (*imprime_info)( const void * );

} avl_arv;

/* Funções para manipulação da árvore */

// Inicialização da árvore
void avl_init ( avl_arv **, int (*compara_info)( const void *, const void * ),
        void (*imprime_info)( const void * ));

// Insere um elemento na árvore
int avl_insert (avl_arv **, no_avl *, no_avl **, void * );

// Remove um elemento da árvore
int avl_remove ( avl_arv **, no_avl **, void * );

// Realiza o percurso em pré-ordem
void avl_walk_pre ( avl_arv *, no_avl * );

// Realiza o percurso em pos-ordem
void avl_walk_pos ( avl_arv *, no_avl * );

// Realiza o percurso em ordem simetrica
void avl_walk_sim ( avl_arv *, no_avl * );

// Realiza o percurso na árvore por nível
void avl_walk_byLevel ( avl_arv * );

// Faz uma busca na árvore
no_avl *avl_search ( avl_arv *, no_avl *, void * );

// Retorna a altura de uma sub-árvore
int avl_height ( no_avl* );

#ifdef __cplusplus
}
#endif


#endif
