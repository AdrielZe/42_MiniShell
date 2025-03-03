/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:32:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/29 16:00:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

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
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			perror("strdup failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		free(node->value);
		node->value = NULL;
	}
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static int	redirection_if(t_tokens *tokens, t_ast_node *node)
{
	if (!tokens->next && node->type != NODE_WORD)
	{
		ft_putstr_fd("Erro de sintaxe!\n", STDERR_FILENO);
		return (0);
	}
	if (tokens->type == TOKEN_REDIRECT_IN)
	{
		node->infile = open_stdin(tokens->next->value);
		node->outfile_type = NODE_REDIRECT_IN;
		return (1);
	}
	else if (tokens->type == TOKEN_REDIRECT_OUT)
	{
		node->outfile = open_stdout(tokens->next->value);
		return (1);
	}
	else if (tokens->type == TOKEN_APPEND)
	{
		node->outfile = open_append(tokens->next->value);
		node->outfile_type = NODE_APPEND;
		return (1);
	}
	return (0);
}

static void	handle_cmd_or_word_token(t_tokens *tokens,
				t_ast_node **root, t_ast_node **current)
{
	char *token_value;

	if (tokens->type == TOKEN_WORD)
	{
		if (tokens->value)
		{
			token_value = extract_word(&tokens->value);
			if (token_value)
			{
				tokens->value = token_value;
			}
		}
		create_word_node(root, current, tokens);
	}
	else
		create_command_node(root, current, tokens);
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
		else if (tokens->type == TOKEN_HEREDOC)
			create_heredoc_node(&root, &current);
		else if (tokens->type == TOKEN_COMMAND || tokens->type == TOKEN_WORD)
			handle_cmd_or_word_token(tokens, &root, &current);
		else if (tokens->type == TOKEN_ENV_VAR)
			create_envp_node(&root, &current, tokens);
		else if (redirection_if(tokens, current))
		{
			if (current && current->infile == -1)
				return (NULL);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (root);
}
