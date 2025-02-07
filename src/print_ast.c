#include "../headers/main.h"
// Essa função não será usada qnd o projeto ficar pronto, apenas para testes, por isso ela está fora da norma
void print_ast(t_ast_node *node, int level)
{
    if (!node)
        return;

    // Indentação para visualizar a hierarquia
    for (int i = 0; i < level; i++)
        printf("  ");
    
    // Exibir o tipo e valor do nó
   if (node->type == NODE_PIPE)
	printf("[%s: %s]\n", "PIPE: ", node->value);
    else if (node->type == NODE_COMMAND)
	printf("[%s: %s]\n", "COMMAND: ", node->value);
    else if (node->type == NODE_HEREDOC)
	printf("[%s: %s]\n", "HEREDOC: ", node->value);

    // Recursão para o filho esquerdo, se houver
    if (node->left)
    {
        for (int i = 0; i < level + 1; i++)  // Mais um nível de indentação para o filho esquerdo
            printf("  ");
        printf("[LEFT]\n");
        print_ast(node->left, level + 1);
    }

    // Recursão para o filho direito, se houver
    if (node->right)
    {
        for (int i = 0; i < level + 1; i++)  // Mais um nível de indentação para o filho direito
            printf("  ");
        printf("[RIGHT]\n");
        print_ast(node->right, level + 1);
    }
}