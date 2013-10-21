/*
---------------------------------------------------------------------------------------------------------------------------------------------
	Programa em linguagem C utilizando padrão ANSI C para uma AVL que armazena somente valores inteiros positivos não repetidos. O usuário tem a qualquer momento,as seguintes opções: Inserção de novo valor(caso o valor já esteja presente na árvore,o programa deve avisar o usuario); e a listagem do conteudo da árvore por níveis(começando pela raiz,percorrendo-se  cada nível da esquerda para a direita,listar o conteúdo de cada nível em formato de lista,incluindo para cada nó a informação do valor armazenado e, entre parênteses,o valor armazenado no pai sendo que para a raiz utilizar NIL para representar o valor do pai).

---------------------------------------------------------------------------------------------------------------------------------------------

Universidade Federal da Fronteira Sul
Curso: Ciência da Computação 
Disciplina: Estrutura de Dados II - 02.2012
Aluna: Silvana Trindade
e-mail: syletri@gmail.com

---------------------------------------------------------------------------------------------------------------------------------------------
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"tadAVL.h"

int main()
{
	int Option,number;
	TREE *T = TREE_Initialize();
	
	printf("***************************************************************\n");
	printf("            Árvore Binária Balanceada em Altura                \n");
	printf("***************************************************************\n\n");

	do {
		
		Option = Menu();
	
		switch(Option) {
			
			case INSERT:
		
				printf("\nDIGITE UM NÚMERO INTEIRO POSITIVO A SER INSERIDO:");
				scanf("%d",&number);

				if(!T)
				{
					break;
				}
				
				if(number < 0)
				{
					printf("\n<<ESSE NÚMERO NÃO É INTEIRO POSITIVO>>\n\n");
				}
				if(TREE_Search(T->Root,number) != NULL)
				{

					printf("\n<<ESSSE NÚMERO JÁ FOI INSERIDO>>\n\n");
					break;
				}

				TREE_Insert(T,SUBTREE_Create(number)); /* Insere nodo na AVL */
				
				break;
			
			case DELETE: {
		
			
				printf("\nDIGITE UM NÚMERO INTEIRO POSITIVO A SER REMOVIDO:");
				scanf("%d",&number);

				if(T->Root == NULL)
				{
					printf("ERROR...AVL VAZIA\n\n");	
					break;
				}
				if(number < 0)
				{
					printf("\n<<ESSE NÚMERO NÃO É INTEIRO POSITIVO>>\n\n");
				}
				if(TREE_Search(T->Root,number) == NULL)
				{

					printf("\n<<ESSE NÚMERO NÃO FOI ENCONTRADO>>\n\n");
					break;
				}

				TREE_Delete(T,TREE_Search(T->Root,number)); /*Deleta nodo */
				
				break;
			}
			case PRINT:
					if(T->Root == NULL)
					{
						printf("\n<<AVL VAZIA>>\n\n");
						
					}
					else
					{
						Imprime(T->Root); /* Imprime árvore */
					}				
				break;
			
			default:

				break;
		}
	}
	while(Option != 4 );

		TREE_Free(T->Root); /* Limpa a árvore */
		free(T);
		printf("\nFIM...\n\n");
		return 0;
}
