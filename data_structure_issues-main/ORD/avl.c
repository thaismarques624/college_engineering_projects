#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //serve para ler acento.

/*Obs.: Codigo em inglês pela fonte de pesquisa,
 mas os comentarios e explicações estão em português*/

struct Node { //criando o nó
  struct Node *left;
  struct Node *right;
  int height;
  int key;
};

int max(int a, int b);

int height(struct Node *N) { //calculcado a altura
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) { //ta recebendo o começo e o fim e comparando.
  return (a > b) ? a : b;
}


struct Node *newNode(int key) { //alocando os nós
  struct Node *node = (struct Node *)
  malloc(sizeof(struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}


struct Node *rightRotate(struct Node *y) { //rotação a direita
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}


struct Node *leftRotate(struct Node *x) { //rotação a esquerda
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}


int getBalance(struct Node *N) { //obtendo o fator de equilibrio
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}


struct Node *insertNode(struct Node *node, int key) { //inserindo os nós e fazendo as comparações para saber onde cada um ficará.

  if (node == NULL)
    return (newNode(key));

  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  //Atualizando o fator de balanceamento e balanceando a arvore.
  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct Node *minValueNode(struct Node *node) { //aqui pega o nó com um valor minimo de chave e faz comparação.
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}


struct Node *deleteNode(struct Node *root, int key) { //função que acha e remove os nós
   if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);

  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      struct Node *temp = minValueNode(root->right);

      root->key = temp->key;

      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == NULL)
    return root;

  //atualizando o fator de balanceamento e balanceando.
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}


void printPreOrder(struct Node *root) { /*Essa função ta printando a pre-ordem:
                                        trata raiz, percorre esquerda, percorre direita*/
  if (root != NULL) {
    printf("\n%d ", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

int main() {
  /*Aqui fica o teste do que foi implementado acima,
    irá chamar, inserir, mostrar e deletar um nó da arvore,
    e ao fim imprime o resultado final na tela.
  */
  setlocale(LC_ALL, "Portuguese"); //Consegue exibir os acentos nos printf.

  struct Node *root = NULL;

  root = insertNode(root, 55);
  root = insertNode(root, 13);
  root = insertNode(root, 14);
  root = insertNode(root, 20);
  root = insertNode(root, 78);
  root = insertNode(root, 36);
  root = insertNode(root, 2);

  printf("Árvore AVL:\n");
  printPreOrder(root);

  root = deleteNode(root, 20);

  printf("\n\nÁrvore AVL Final(Já com o delete e balanceada):\n ");
  printPreOrder(root);

  return 0;
}
