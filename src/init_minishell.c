/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:36:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/28 01:20:41 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

static void	exit_if_typed_exit(char *input,
			t_tokens **token_list, char **envp_copy)
{
	if (ft_strcmp("exit", input) == 0)
	{
		clear_token_list(token_list);
		free_array(envp_copy, array_len(envp_copy));
		free(input);
		printf("Saindo do programa.\n");
		exit(0);
	}
}

void	free_token(char ***token)
{
    if (!*token)
        return;
    for (int i = 0; (*token)[i]; i++)
        free((*token)[i]); // Libera cada string no array
    free(*token); // Libera o array
    *token = NULL;
}

void	init_shell(char ***token, t_tokens **token_list, char
			**envp, t_ast_node **root)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			handle_ctrl_d(envp, token_list, *root);
		if (!input || ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		exit_if_typed_exit(input, token_list, envp);
		*token = tokenize(input);
		classify_token(*token, token_list);
		print_list(*token_list);
		*root = build_ast(*token_list);
		parse_commands(*root, envp);
		if (input)
			add_history(input);
		free(input);
		input = NULL;
		free_token(token);
	}
}
