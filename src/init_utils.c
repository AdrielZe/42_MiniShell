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
		handle_ctrl_d(envp, token_list, root);
}

void	setup_tokens_and_build_ast(char *input,
	t_tokens **token_list, char **envp, char ***token)
{
	exit_if_typed_exit(input, token_list, envp);
	*token = tokenize(input, envp);
	if (!*token)
	{
		// free_array(*token, array_len(*token));
		clear_token_list(token_list);
		return ;
	}
	classify_token(*token, token_list);
	free_array(*token, array_len(*token));
}
