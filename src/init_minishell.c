/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:36:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/05 19:31:50 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
void print_indent(int level)
{
    for (int i = 0; i < level; i++)
        printf("  ");
}

// Função recursiva para imprimir a árvore de comandos
void print_ast_tree(t_ast_node *node, int level)
{
    if (!node)
        return;
    
    print_indent(level);
    
    if (node->type == NODE_PIPE)
        printf("[PIPE]\n");
    else if (node->type == NODE_COMMAND)
        printf("[COMMAND]: %s\n", node->value ? node->value : "(null)");
    else
        printf("[UNKNOWN NODE TYPE]\n");
    
    if (node->left)
    {
        print_indent(level);
        printf("LEFT ->\n");
        print_ast_tree(node->left, level + 1);
    }
    
    if (node->right)
    {
        print_indent(level);
        printf("RIGHT ->\n");
        print_ast_tree(node->right, level + 1);
    }
}
static void	exit_if_typed_exit(char *input)
{
	if (ft_strcmp("exit", input) == 0)
	{
		printf("Saindo do programa.\n");
		exit(0);
	}
}

static void	free_token(char ***token)
{
	if (*token)
		free(*token);
	*token = NULL;
}

void	init_shell(char ***token, t_tokens **token_list, char
			*envp[], t_ast_node **root)
{
	char	*input;

	while (1)
	{
		input = readline("Digite algo> ");
		if (!input || ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		exit_if_typed_exit(input);
		*token = tokenize(input, ' ');
		classify_token(*token, token_list);
		if (ft_strcmp((*token_list)->value, "echo") == 0)
			echo(*token_list);
		else
		{
			*root = build_ast(*token_list);
			print_ast_tree(*root, 0);
			parse_commands(*root, envp);
		}
		if (input)
			add_history(input);
		input = NULL;
		free_token(token);
	}
}
