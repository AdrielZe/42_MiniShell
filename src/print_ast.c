# include "../headers/main.h"

void print_ast(t_ast_node *node, int level)
{
    if (!node)
        return;

    // Indentação para visualizar a hierarquia
    for (int i = 0; i < level; i++)
        printf("  ");
    
    // Exibir o tipo e valor do nó
    printf("[%s: %s]\n", node->type == NODE_PIPE ? "PIPE" : "COMMAND", node->value);

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
