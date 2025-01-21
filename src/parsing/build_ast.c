/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:32:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/21 17:05:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

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


//char    test_ast()

void free_ast(t_ast_node *node) 
{
    if (!node)                      
        return ;
    free_ast(node->left);      
    free_ast(node->right);      
    if (node->value)        
        free(node->value);
    free(node);
}

t_ast_node	*create_node(t_node_type type, char *value)
{
    t_ast_node	*node;
    
    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->type = type;
    node->value = ft_strdup(value); 
    node->left = NULL;
    node->right = NULL;
    return (node); 
}

t_ast_node	*build_ast(t_tokens *tokens)
{
	t_ast_node	*root;
	t_ast_node	*current;

	current = NULL;
	root = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
		{
			t_ast_node	*pipe_node;

			pipe_node = create_node(NODE_PIPE, "|");
            pipe_node->left = root;   // O comando anterior será o filho esquerdo do PIPE
            root = pipe_node;
            current = root;
		} else if (tokens->type == TOKEN_COMMAND)
        {
            t_ast_node *command_node = create_node(NODE_COMMAND, tokens->value);
            if (!root)
                root = command_node;
            else if (current)
                current->right = command_node;
            current = command_node;
        }
        tokens = tokens->next;
	}    
    print_ast(root, 0);
	return (root);
}