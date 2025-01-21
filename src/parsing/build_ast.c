/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:32:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/21 18:25:47 by marvin           ###   ########.fr       */
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


// char    test_ast(t_ast  *node)
// {
    
// }

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
            pipe_node->left = root;
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

char *concatenate_commands(t_ast_node *node) {
    if (!node)
        return NULL;

    char *result = malloc(1);
    result[0] = '\0';

    if (node->type == NODE_COMMAND) {
        // logica para procurar o comando (funcao) , e se for valido, direcionar o retorno para um pipe e passar para o proximo processo
        result = realloc(result, strlen(result) + strlen(node->value) + 1);
        strcat(result, node->value);
    }

    if (node->left) {
        char *left_result = concatenate_commands(node->left);
        result = realloc(result, strlen(result) + strlen(left_result) + 1);
        strcat(result, left_result);
        free(left_result);
    }

    if (node->right) {
        char *right_result = concatenate_commands(node->right);
        result = realloc(result, strlen(result) + strlen(right_result) + 1);
        strcat(result, right_result);
        free(right_result);
    }

    return result;
}
