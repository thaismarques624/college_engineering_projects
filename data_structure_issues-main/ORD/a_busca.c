#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //serve para exibir acento.


struct node { //criando a estrutura do n�
    struct node *left, *right;
    int key;
};


struct node *newNode(int item) { //criando o n�
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


struct node *insert(struct node *node, int key) { //estrutura com as condi��es para inserir o n�

  if (node == NULL) return newNode(key); //retorna um novo n� se a �rvore estiver vazia.

  //condi��es que checam o lugar certo para inserir o n�
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

struct node *minValueNode(struct node *node) { //essa estrutura server para achar o n� sucessor.
  struct node *current = node;

   while (current && current->left != NULL) //checa a folha a esquerda.
    current = current->left;

  return current;
}


struct node *deleteNode(struct node *root, int key) { // estrutura com condi��es para deletar um elemento.

  if (root == NULL) return root; // teste para �rvore vazia.

 //testes para achar o elemento a ser deletado.
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    // Se o n� estiver com apenas um filho ou nenhum filho
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // Se o n� tiver dois filhos
    struct node *temp = minValueNode(root->right);

    // Coloca o sucessor de ordem na posi��o do n� a ser exclu�do
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

  printf("\n\nImprimindo a �rvore em ordem: \n ");
  inorder(root);

  root = deleteNode(root, 7);
  printf("\n\nImprimindo a �rvore depois de deletar o 7: \n");
  inorder(root);
}


