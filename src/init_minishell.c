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

static t_ast_node	*process_ast(t_ast_node **root,
			t_tokens **token_list, char **envp)
{
	int	save_stdout;

	save_stdout = dup(STDOUT_FILENO);
	if (!token_list || !*token_list)
		return (NULL);
	if (check_syntax(*token_list, envp))
	{
		*root = build_ast(*token_list);
		clear_token_list(token_list);
		parse_commands(*root, envp);
		open_exitcode();
	}
	else
		clear_token_list(token_list);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	return (*root);
}

void	setup_and_build(char **input,
		t_tokens **token_list, char **envp, t_ast_node **root)
{
	char	**token;

	token = NULL;
	setup_tokens_and_build_ast(*input, token_list, envp, &token);
	*root = process_ast(root, token_list, envp);
}

void	process_input_loop(char **input,
		char **envp, t_tokens **token_list, t_ast_node **root)
{
	while (1)
	{
		set_signal_handler(handle_sigint);
		manage_rl_input(input, envp, token_list, *root);
		if (!(*input) || ft_strlen(*input) == 0)
		{
			free(*input);
			continue ;
		}
		if (ft_exit(*input, envp, token_list, *root) == 1)
			return ;
		setup_and_build(input, token_list, envp, root);
		if (*root)
		{
			free_ast(*root);
			*root = NULL;
		}
		if (*input)
			add_history(*input);
		free(*input);
		*input = NULL;
	}
}

void	init_shell(char ***token,
		t_tokens **token_list, char **envp, t_ast_node **root)
{
	char	*input;

	input = NULL;
	*token = NULL;
	process_input_loop(&input, envp, token_list, root);
}
