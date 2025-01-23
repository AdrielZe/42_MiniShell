/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:32:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/22 17:03:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

// Essa função não será usada qnd o projeto ficar pronto, apenas para testes, por isso ela está fora da norma
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

void	free_ast(t_ast_node *node)
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
			create_pipe_node(&root, &current);
		else if (tokens->type == TOKEN_COMMAND)
			create_command_node(&root, &current, tokens);
		tokens = tokens->next;
	}
	print_ast(root, 0);
	return (root);
}

char	*parse_commands(t_ast_node *node)
{
	char	*result;
	char	*left_result;
	char	*right_result;

	left_result = NULL;
	right_result = NULL;
	if (!node)
		return (NULL);
	result = malloc(1);
	result[0] = '\0';
	if (node->type == NODE_COMMAND)
	{
	// logica para procurar o comando (funcao) ,
	// e se for valido, direcionar o retorno para um pipe e passar para o proximo processo
		result = ft_realloc(result, ft_strlen(result) + ft_strlen(node->value) + 1);
		ft_strcat(result, node->value);
	}
	if (node->left)
	{
		left_result = parse_commands(node->left);
		result = ft_realloc(result, ft_strlen(result) + ft_strlen(left_result) + 1);
		ft_strcat(result, left_result);
		free(left_result);
	}
	if (node->right)
	{
		right_result = parse_commands(node->right);
		result = ft_realloc(result, ft_strlen(result) + ft_strlen(right_result) + 1);
		ft_strcat(result, right_result);
		free(right_result);
	}
	return (result);
}
