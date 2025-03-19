/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:36:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/28 17:40:09 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	g_exit;

void	exit_if_typed_exit(char *input,
			t_tokens **token_list, char **envp_copy)
{
	if (ft_strcmp("exit", input) == 0)
	{
		clear_token_list(token_list);
		free_array(envp_copy);
		free(input);
		printf("Exiting.\n");
		exit(0);
	}
}

void	free_token(char ***token)
{
	int	i;

	if (!*token)
		return ;
	i = 0;
	while ((*token)[i])
	{
		free((*token)[i]);
		i++;
	}
	free(*token);
	*token = NULL;
}

int	check_syntax(t_tokens *tokens)
{
	t_tokens	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_APPEND || current->type == TOKEN_HEREDOC
			|| current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT)
		{
			if (!current->next || (current->next->type != TOKEN_WORD
					&& current->next->type != TOKEN_COMMAND
					&& current->next->type != TOKEN_SIMPLE_QUOTE))
			{
				printf("Syntax error: \n");
				add_exitcode(2);
				return (0);
			}
		}
		if (current->type == TOKEN_PIPE)
		{
			if (!current->next || (current->next
					&& current->next->type == TOKEN_PIPE))
			{
				printf("Syntax error: pipes\n");
				add_exitcode(2);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

static t_ast_node	*process_ast(t_ast_node **root,
			t_tokens **token_list, char **envp)
{
	int	save_stdout;

	save_stdout = dup(STDOUT_FILENO);
	if (!token_list || !*token_list)
		return (NULL);
	if (check_syntax(*token_list))
	{
		*root = build_ast(*token_list);
		clear_token_list(token_list);
		parse_commands(*root, envp);
		add_exitcode(g_exit);
	}
	else
		clear_token_list(token_list);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	return (*root);
}

void	init_shell(char ***token, t_tokens **token_list, char
			**envp, t_ast_node **root)
{
	char	*input;
	char	*str_exit;

	*token = NULL;
	while (1)
	{
		set_signal_handler(handle_sigint);
		manage_rl_input(&input, envp, token_list, *root);
		if (!input || ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		if (ft_exit(input, envp, token_list, *root) == 1)
			return ;
		setup_tokens_and_build_ast(input, token_list, envp, token);
		*root = process_ast(root, token_list, envp);
		if (*root)
		{
			free_ast(*root);
			*root = NULL;
		}
		if (input)
			add_history(input);
		free(input);
		input = NULL;
	}
}
