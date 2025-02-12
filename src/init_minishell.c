/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:36:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/11 20:38:52 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

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
		*token = tokenize(input);
		classify_token(*token, token_list);
		if (ft_strcmp((*token_list)->value, "echo") == 0)
			echo(*token_list);
		else
		{
			*root = build_ast(*token_list);
			parse_commands(*root, envp);
		}
		//print_ast(*root, 0);
		if (input)
			add_history(input);
		input = NULL;
		free_token(token);
	}
}
