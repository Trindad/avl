/* Tads para AVL */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define INSERT 1
#define DELETE 2
#define PRINT 3

typedef struct _SubTree {      			/* Estrutura do Nodo */

	int key;               			/* Chave */
	int balance;           			/* Fator de balanceamento */
	int height;            			/* Altura da árvore */
	struct _SubTree *right;			/* Ponteiro para direita da Subárvore */
	struct _SubTree *left; 			/* Ponteiro para esquerda da Subárvore */
	struct _SubTree *root; 			/* Ponteiro para a raíz da Subárvore */

}SUBTREE;

typedef struct _TREE {         			/* Estrutura da árvore */

	struct _SubTree *Root; 			/* Ponteiro para a raíz */ 
	
}TREE;

int Menu();                                  	/* Menu principal com as opções de uma AVL */

void Print_Out(SUBTREE *x);            		/* Imprime AVL por nível */

void Imprime(SUBTREE *x); 			/* Imprime a árvore AVL por nível */

void Print_List(SUBTREE *x,int counter,int level);/*Lista nivel pelo metodo pré-ordem */

SUBTREE *Rotate_Two_Left(TREE *T,SUBTREE *x);	/* Rotação a esquerda */

SUBTREE *Rotate_Right(TREE *T,SUBTREE *x);   	/* Rotação a direita */

SUBTREE *Rotate_Two_Right(TREE *T,SUBTREE *x); 	/* Rotação duplo a esquerda */

SUBTREE *Rotate_Two_Left(TREE *T,SUBTREE *x);   /* Rotação duplo a direita */

SUBTREE *Test_Rotation(TREE *T,SUBTREE *x);	/* Testa se a rotação será a direita ou a esquerda */

int SUBTREE_CalcBalance(SUBTREE *T); 		/* Calcula o Fator de Balanceamento */

SUBTREE *SUBTREE_Height(SUBTREE *x);		/* Calcula o tamanho ou altura da árvore */

SUBTREE *TREE_Search_CheckUp(SUBTREE *x);	/* Rebalanceia a árvore e recalcula a altura */

void Delete_Fixup(TREE *T,SUBTREE *x);          /* Função para verificar desbalanceamento e e recalcular altura e fator de balanceamento após remoção */

SUBTREE *TREE_Search(SUBTREE *T,int key); 	/* Percorre a árvore */

SUBTREE *SUBTREE_Minimun(SUBTREE *x); 		/* Encontra elemento mínimo na árvore ou subárvore */

SUBTREE *SUBTREE_Sucessor(SUBTREE *x); 		/* Encontra o nodo sucessor em uma árvore */

TREE *TREE_Initialize(); 			/* Inicializa a árvore AVL*/

SUBTREE *SUBTREE_Create(int key); 		/* Aloca o nó para as subárvores */

TREE *TREE_Insert(TREE *T,SUBTREE *z); 		/* Insere elementos na árvore */

void TREE_Delete(TREE *T,SUBTREE *z); 		/* Deleta ou exclui um elemento inteiro da arvore */

void TREE_Free(SUBTREE *T); 			/* Libera a memória ocopuda pela AVL*/
