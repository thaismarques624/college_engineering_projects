#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //serve para exibir acento.


struct node { //criando a estrutura do nó
    struct node *left, *right;
    int key;
};


struct node *newNode(int item) { //criando o nó
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}


void inorder(struct node *root) { //configurando a ordem e como vai ser exibida
  if (root != NULL) {

    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
  }
}


struct node *insert(struct node *node, int key) { //estrutura com as condições para inserir o nó

  if (node == NULL) return newNode(key); //retorna um novo nó se a árvore estiver vazia.

  //condições que checam o lugar certo para inserir o nó
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

struct node *minValueNode(struct node *node) { //essa estrutura server para achar o nó sucessor.
  struct node *current = node;

   while (current && current->left != NULL) //checa a folha a esquerda.
    current = current->left;

  return current;
}


struct node *deleteNode(struct node *root, int key) { // estrutura com condições para deletar um elemento.

  if (root == NULL) return root; // teste para árvore vazia.

 //testes para achar o elemento a ser deletado.
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    // Se o nó estiver com apenas um filho ou nenhum filho
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // Se o nó tiver dois filhos
    struct node *temp = minValueNode(root->right);

    // Coloca o sucessor de ordem na posição do nó a ser excluído
    root->key = temp->key;

    // deletando o sucessor pedido
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}


int main() {
    //Aqui fica o teste do que foi implementado acima.

  setlocale(LC_ALL, "Portuguese"); //Consegue exibir os acentos nos printf.

  struct node *root = NULL;
  root = insert(root, 88);
  root = insert(root, 34);
  root = insert(root, 17);
  root = insert(root, 63);
  root = insert(root, 7);
  root = insert(root, 102);
  root = insert(root, 141);
  root = insert(root, 47);

  printf("\n\nImprimindo a árvore em ordem: \n ");
  inorder(root);

  root = deleteNode(root, 7);
  printf("\n\nImprimindo a árvore depois de deletar o 7: \n");
  inorder(root);
}


