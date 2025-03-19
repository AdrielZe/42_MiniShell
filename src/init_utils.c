/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:52:02 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/05 21:20:21 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	manage_rl_input(char **input,
		char **envp, t_tokens **token_list, t_ast_node *root)
{
	*input = readline("> ");
	if (*input == NULL)
	{
		handle_ctrl_d(envp, token_list, root);
	}
}

void	setup_tokens_and_build_ast(char *input,
	t_tokens **token_list, char **envp, char ***token)
{
	char	**input_split;

	input_split = split_with_quotes(input);
	if (!input_split)
		return ;
	if (ft_strcmp(input_split[0], "exit") == 0)
	{
		free_array(input_split);
		return;
	}
	free_array(input_split);
	*token = tokenize(input, envp);
	if (!*token)
	{
		clear_token_list(token_list);
		return ;
	}
	classify_token(*token, token_list);
	free_array(*token);
	*token = NULL;
}
