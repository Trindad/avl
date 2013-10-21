/*Funções para uma AVL: Inserção,remoção,deslocamento,balanceamento*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"tadAVL.h"

/* Menu principal dispõe ao usuario as seguintes opções:inserir,remover,imprimir e sair,para escolher uma opção basta digitar o numero correspondente a mesma */

int Menu() { 
	
	int option;

	printf("---------------------------------------------------------------\n");
	printf("|                    MENU ÁRVORE AVL:                         |\n");
	printf("---------------------------------------------------------------\n");
	printf("|  -->             DIGITE [1] para INSERÇÃO             <--   |\n");
	printf("|  -->             DIGITE [2] para REMOÇÃO              <--   |\n");
	printf("|  -->             DIGITE [3] para IMPRIMIR             <--   |\n");
	printf("|  -->             DIGITE [4] para SAIR                 <--   |\n");
	printf("---------------------------------------------------------------:");
	scanf("%d",&option);

	return option;

}

void Print_Out(SUBTREE *T) { /*Função para imprimir a arvore em AVL*/

	
	if(T != NULL)
	{
		printf("Chave: %d balance : %d H: %d \n", T->key,T->balance,T->height);;
		if(T->root != NULL)
		{
			printf(" (%d)\n",T->root->key);
		} 
		else 
		{
			printf(" (NIL)\n");			
		}

		Print_Out(T->left);
		Print_Out(T->right);
	}
	
}
/* Imprime a árvore por níveis */

void Imprime(SUBTREE *x) {

    	if(x == NULL)
	{
        	printf("\nÁrvore VAZIA.\n");
	}
	else
	{
        	int level;/* variavel para controle do nível */

		for(level = 0; level <= x->height; level++) {

		    printf("\nNÍVEL %d: ", level); /* Imprime o nível */
		    Print_List(x, -1, level);
		}
    	}
    	printf("\n");

}

/* Função recursiva para imprimir a esquerda e direita de um nivel passado na função Imprime baseada em pré-ordem onde vizita a raíz primeiro depois percorre a esquerda e a direita tendo um contadodor para poder imprimir somente a chave em determinado nivel */	

void Print_List(SUBTREE *x,int counter,int level) { 

	if(x != NULL)
	{
		counter++;
		Print_List(x->left, counter, level);
		Print_List(x->right, counter, level);
    	}
    	if( x != NULL && level == counter) /*quando o counter for igual ao nivel então imprime */
	{ 

       		printf("%d ", x->key);

		if(x->root == NULL)  /* Se for a raiz imprime como seu root o NIL*/ 
		{
		    printf("(NIL).");
		}
		else
		{
		    printf("(%d). ", x->root->key);
		}
	}
	else if(counter > level) /* contador maior que o número de níveis */
	{
        	return;
	}
}

 /* Rotação simples a esquerda */

SUBTREE *Rotate_Left(TREE *T,SUBTREE *x) { 
	
	if(x == NULL || T == NULL )
	{
		return NULL;
	}   

	SUBTREE *y = NULL; 

	y = x->right; /* Define y */
	
	x->right = y->left; /* Faz da subárvore esquerda de y a subárvore a direita de x */
		
	
	if (y->left != NULL)
	{
		y->left->root = x; /*Liga o root de x a y*/
	}
	y->root = x->root; /*Liga o root de x a y */
	if (x->root == NULL)
	{
		T->Root = y;
	}
	else if (x == x->root->left)
	{
		x->root->left = y;
	}
	else
	{
		x->root->right = y;
	}
	y->left = x; /* Coloca x a esquerda de y */
	x->root = y;
	return y;
	
}

/*Rotação simples a direita */
	
SUBTREE *Rotate_Right(TREE *T,SUBTREE *x) {  
	
	if(x == NULL || T == NULL )
	{
		
		return NULL;
	}

	SUBTREE *y = NULL;

	y = x->left; /* Define y */
	
	x->left = y->right;/* Faz da subárvore direita de y a subárvore a esquerda de x */

	if (y->right != NULL)
	{
		y->right->root = x; /*Liga o root de x a y*/
	}

	y->root = x->root; /*Liga o root de x a y */

	if (x->root == NULL)
	{
		T->Root = y;
	}
	else if (x == x->root->right)
	{
		x->root->right = y;
	}
	else
	{
		x->root->left = y;
	}
	y->right = x;/* Coloca x a direita de y */
	x->root = y;
	return y;
}

/* Rotação dupla a direita da árvore, onde recebe duas estruturas do tipo ponteiros, um do tipo árvore e outro subárvore */

SUBTREE *Rotate_Two_Right(TREE *T,SUBTREE *x) { /*Rotação Dupla a direita */
	
	if(x == NULL || T == NULL )
	{
		return NULL;
	}
	
	x->left = Rotate_Left(T, x->left);
	Rotate_Right(T, x);
	return x;
}

/* Rotação dupla a esquerda da árvore, onde recebe como parametro dois ponteiros, um do tipo árvore e outro subárvore */
	
SUBTREE *Rotate_Two_Left(TREE *T,SUBTREE *x) { 

	if(x == NULL || T == NULL )
	{
		return NULL;
	}
	x->right = Rotate_Right(T,x->right);
	Rotate_Left(T,x);
	return x;
}
		
/* Testa se a rotação será a direita ou a esquerda e se haver caso de dupla rotação, passando como parametro para as funções de rotação sempre a árvore e a subárvore que esta desbalanceada */

SUBTREE *Test_Rotation(TREE *T, SUBTREE *x) { 

	if(x == NULL)
	{
		return NULL;	
	}
	/* Arvore pende para a direita então as rotações serão realizadas a esquerda */
	if(x->balance == -2)
	{
		if(x->right->balance == -1 || x->right->balance == 0)
		{
			Rotate_Left(T,x);
			
			return x;
		}
		else if(x->right->balance == 1)
		{
			Rotate_Two_Left(T,x);
			return x;
		}
		
	}
	/* Arvore pende para a esquerda então as rotações serão realizadas a direita */
	else if(x->balance == 2)
	{
		if(x->left->balance == 1 || x->left->balance == 0)
		{	
			Rotate_Right(T,x);
			return x;
		}
		else if(x->left->balance == -1)
		{
			Rotate_Two_Right(T,x);
			return x;
		}
		return x;
		
	}
	
	return NULL;
}

/* Encounterra o menor elemento da árvore */

SUBTREE *SUBTREE_Minimun(SUBTREE *x) { 

	while(x->left != NULL) /*Enquanto a esquerda for rightente NULL ele procura o menos valor*/
	{
		x = x->left;
	}
	return x;
}

/* Encounterra o sucessor de um número. Percorrendo a direita da raíz da subtree até encounterrar a esquerda(Utilizando função MINIMUN) o elemento com menor valor*/
	
SUBTREE *SUBTREE_Sucessor(SUBTREE *x) {

	SUBTREE *y = NULL;

	if(x->right != NULL)
	{

		return (SUBTREE_Minimun(x->right));
	}
	
	/* Para encounterrar y,sobe a árvore apartir de x até encounterrarmos um nó que seja o filho a esquerda de seu root isso ocorre nas linhas 	274 a 281 */
	y = x->root;

	while(y != NULL && x == y->right)
	{
		x = y;
		y = y->root;
	}

	return y;
	
}

/* Calcula o Fator de Balancemento da árvore AVL retornando-o */
	
int SUBTREE_CalcBalance(SUBTREE *T) { 

	if(T == NULL)
	{
		return -1;
	}

	int h_left = T->left == NULL ? -1 : T->left->height;
	int h_right = T->right == NULL ? -1 : T->right->height;

	return h_left - h_right; /* Retorna balanceamento calculado por : (height esquerda - height direita) */

}

/*Calcula a height retornando o nó desbalanceado caso encounterre ao chamar a função de balanceamento*/

SUBTREE *SUBTREE_Height(SUBTREE *x) { 

	if(x == NULL)
	{
		return NULL;
	}
	/*Alterar height de baixo pra cima se necesssario */

	if (x->root != NULL)
	{
		SUBTREE *root = x->root;
		SUBTREE *hold = NULL;

		x->root->balance = SUBTREE_CalcBalance(x->root); /* recebe o fator de balanceamento*/
		if(x->key < x->root->key) 
		{

			if(x->root->right != NULL)
			{
				if(x->root->right->height > x->height)
				{
					root->height = x->root->right->height + 1; /* height de x é incrementada */
				}
				else
				{
					root->height = x->height + 1; /* height de x é incrementada */
				}
			}
			else
			{
				root->height = x->height + 1; /* height de x é incrementada */
			}
		}
		else if(x->key > x->root->key) 
		{

			if(x->root->left != NULL)
			{
				if(x->root->left->height > x->height)
				{
					root->height = x->root->left->height + 1; /* height de x é incrementada */
				}
				else
				{
					root->height = x->height + 1; /* height de x é incrementada */
				}
			}
			else
			{
				root->height = x->height + 1; /* height de x é incrementada */
			}
		}
		hold = SUBTREE_Height(root); /* chama função recursivamente */
		
		if (x->root->balance == 2 || x->root->balance == -2) /* confere se houve a quebra da invariante */
		{
			return x->root; /* Retorna nó desbalanceado */
		}
		else
		{
			return hold; /* Retorna hold onde é NULA */
		}
	}

	return NULL;
}

/* Percorre a árvore  para encounterrar a chave*/

SUBTREE *TREE_Search(SUBTREE *T,int key) { 

	while(T != NULL && key != T->key)
	{
		if(key < T->key)
		{
			T = T->left;
		}
		else
		{
			T = T->right;
		}
	}
	return T;
}

/* Percorre a árvore fazendo o rebalanceamento e calculando a height novamente em pós-ordem ou seja vizita as folhas depois a raíz */

SUBTREE *TREE_Search_CheckUp(SUBTREE *x) { 	
	
	
	if(x != NULL)
	{	
		if(x->left == NULL && x->right == NULL)
		{
			x->balance = 0;
			x->height = 0;
		}
		TREE_Search_CheckUp(x->left);
		TREE_Search_CheckUp(x->right);
		
		SUBTREE_Height(x);
		if(x->left && x->right)
		{
			if(x->left->height >= x->right->height)
			{
				x->height = x->left->height+1;
			}
			else 
			{
				x->height = x->right->height+1;	
			}
		}
		
	}
	return x;
}

/* Função de Rebalanceamento para Remoção de um nó */

void Delete_Fixup(TREE *T,SUBTREE *x) {

	if(x->root->left == NULL && x->root->right == NULL) /* caso x não tiver filhos então atulaliza sua altura e balanceamento para 0(zero)*/
	{
		x->root->balance = 0;
		x->root->height = 0;
		SUBTREE_Height(x->root);
	}
	else if(x->root->left == NULL && x->root->right != NULL) /* caso x tem filho somente a sua direita assume altura da direita + 1 */
	{
		x->root->balance = (-x->root->right->height - 1) ;
		x->root->height = x->root->right->height + 1;
	}
	else if(x->root->left != NULL && x->root->right == NULL)/* caso x tem filho somente a sua esquerda assume altura da esquerda + 1 */
	{
		x->root->balance = x->root->left->height + 1;
		x->root->height = x->root->left->height + 1;
	}
	else if(x->root->left != NULL && x->root->right != NULL) /* caso x tiver filhos a direita e a esquerda da raiz */
	{
		if(x->root->right->height > x->root->left->height) /* Verifica se a altura a direita da raiz de x é maior do a esquerda */
		{
			x->root->balance = x->root->left->height - x->root->right->height;
			x->root->height = x->root->right->height + 1;
		}
		else if(x->root->right->height < x->root->left->height)/* Verifica se a altura a direita da raíz de x é menor que a esquerda */
		{
			x->root->balance = x->root->left->height - x->root->right->height;
			x->root->height = x->root->left->height + 1;
		}
		else if(x->root->right->height == x->root->left->height) /* Verifica se são iguais */
		{
			if(x->root->left == x) /* Se a esquerda da raiz de x estiver o nodo a ser removido então o fator de balancemento será negativo  pois x penderá a esquerda*/
			{
				x->root->balance = (-1) - x->root->right->height;
			}
			else if(x->root->right == x) /* Se a direita da raiz de x estiver o nodo a ser removido então o fator de balancemento será positivo pois x penderá a direita*/
			{
				x->root->balance = x->root->left->height + 1;
			}
			else
			{
				x->root->balance = x->root->left->height - x->root->right->height;
			}		
			x->root->height = x->root->right->height + 1;	
		}
		SUBTREE_Height(x->root);
		
	}
	/* Verifica se x precisará ser balanceado */
	if( x->root->balance < -1 && x->root->height > 1)  /* nodo tende a direita chama função de balanceamento a esquerda */
	{
		if(x->root->right->balance == -1 || x->root->right->balance == 0) /* Rotação simples */
		{
			Rotate_Left(T,x->root);
			
		}
		else if(x->root->right->balance == 1)  /* Rotação dupla */
		{
			x->root->right = Rotate_Right(T,x->root->right);
			TREE_Search_CheckUp(x->root);
			Rotate_Left(T,x->root);
		}
		TREE_Search_CheckUp(x->root);
	}
	else if(x->root->balance > 1  && x->root->height > 1)  /* nodo tende a esquerda chama função de balanceamento a direita */
	{
		if(x->root->left->balance == 1 || x->root->left->balance == 0)/* Rotação simples */
		{
			Rotate_Right(T,x->root);
		}
		else if(x->root->left->balance == -1) /* Rotação dupla */
		{
			x->root->left = Rotate_Left(T, x->root->left);
			TREE_Search_CheckUp(x->root);
			Rotate_Right(T, x->root);
		}
		TREE_Search_CheckUp(x->root);
	}
	if(x->root != NULL && T->Root->height > 1) {

		SUBTREE * w = NULL;

		w = SUBTREE_Height(x->root);
		if(w == NULL)
		{
			return;
		}
		else if(w != NULL && ( w->balance > 1 || w->balance < -1)) /*Uma rotação não foi suficiente */
		{
			Test_Rotation(T,w);
			TREE_Search_CheckUp(T->Root);
		}
	}
	if(T->Root->balance == -2 || T->Root->balance == 2 ) /* A raiz da árvore desbalanceou */
	{
		Delete_Fixup(T,x->root);
	}
	
}
	
 /* Inicializa a árvore AVL  utilizando malloc */
		
TREE *TREE_Initialize() {
	
	TREE *T = (TREE*) malloc ( sizeof (TREE) );

	if(!T)
	{
		return NULL;
	}
	T->Root = NULL;	/* ponteiro inicializado para a raiz da árvore */
	return T;

}

 /*Criar x da Subárvore utilizando malloc*/

SUBTREE *SUBTREE_Create(int key) {
	
	SUBTREE *Sub_Tree = (SUBTREE*) malloc ( sizeof (SUBTREE) );
	
	if(!Sub_Tree)
	{
		return NULL;
	}
	Sub_Tree->right = NULL;
	Sub_Tree->left = NULL;
	Sub_Tree->root = NULL;
	Sub_Tree->balance = 0;
	Sub_Tree->height = 0;
	Sub_Tree->key = key;
	
	return Sub_Tree;
	
}

/* Insere em uma AVL numeros inteiros */
	
TREE *TREE_Insert(TREE *T,SUBTREE *z) {
	
	SUBTREE *hold = T->Root,*y = NULL;
	

	while(hold != NULL)
	{
		y = hold;

		if(z->key < hold->key)
		{
			hold = hold->left;
		}
		else
		{
			hold = hold->right;
		}
		
	}
	z->root = y;

	if(y == NULL) /* Insere na árvore vazia */
	{
		T->Root = z;
		return T;
	}
	
	else if(z->key < y->key) /*Insere Subárvore  esquerda */
	{
			y->left = z;
			SUBTREE *x = NULL;
			x = SUBTREE_Height(z);
			if(x != NULL) /* Verifica se haverá rotações */
			{
				Test_Rotation(T,x);
				TREE_Search_CheckUp(T->Root);	
			}
				
	}
	else /* Insere Subárvore a direita */
	{
			y->right = z;
			SUBTREE *x = NULL;
			x = SUBTREE_Height(z);
			if(x != NULL) /* Verifica se haverá rotações */
			{
				Test_Rotation(T,x);
				TREE_Search_CheckUp(T->Root);
			}
	}
	
	return T;					
}

/* Deleta um x da árvore */

void TREE_Delete(TREE *T,SUBTREE *z) { 

	if(z == NULL) /* z é um ponteiro nulo */
	{
		return;
	}
	SUBTREE *y = NULL,*x = NULL;

	if(z->left == NULL || z->right == NULL) /* z não possui filhos a esquerda ou a direita */
	{
		y = z;
				
	}
	else
	{
		y = SUBTREE_Sucessor(z); /* y recebe o sucessor de z */
	}
	if(y->left != NULL)
	{
		x = y->left; /* x recebe a esquerda de y */
		
	}
	else
	{
		x = y->right; /* x recebe a direita de y */
	}	
	if(x != NULL)
	{
		x->root = y->root; /* a raiz de x recebe a raíz de y */
	}
	if(y->root == NULL)
	{
		T->Root = x; /* Raiz da árvore recebe x */
	}
	else if(y == y->root->left)
	{
		y->root->left = x; /* y que aponta para a raiz a esquerda recebe x */
	}
	else
	{
		y->root->right = x; /*  y que aponta para a raiz a direita recebe x */
	}
	if(y != z)
	{
		z->key = y->key; /* Copia de dados */
	}

	/* Verificar balanceamento e recalcular altura */

	if(T->Root != NULL && T->Root->height > 1) {

		Delete_Fixup(T,y);
	}
	else if(T->Root != NULL && T->Root->height == 1)
	{
		TREE_Search_CheckUp(T->Root);
		
	}
	free(y);
}

 /*Free na árvore inteira seguindo conceito de pós-ordem */

void TREE_Free(SUBTREE *T) {
		

	if(T != NULL)
	{
		TREE_Free(T->left);
		TREE_Free(T->right);
		free(T);
	}
}			
