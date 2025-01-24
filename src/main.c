/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:56:21 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/24 14:08:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include "../headers/tokenize.h"
#include "../headers/parsing.h"

int	main(int argc, char *argv[], char **envp)
{
	char			*input;
	char			**token;
	t_tokens		*token_list;
	t_ast_node		*root;

	if (!argc && ! argv)
		printf("Ok");
	token_list = NULL;
	while (1)
	{
		input = readline("Digite algo> ");
		if (ft_strcmp("exit", input) == 0)
		{
			printf("Saindo do programa.\n");
			break ;
		}
		token = tokenize(input, ' ');
		classify_token(token, &token_list);
		if (strcmp(token_list->value, "echo") == 0)
			echo(token_list);
		else
		{
			root = build_ast(token_list);
			parse_commands(root, envp);
		}
		if (*input)
			add_history(input);
		free(input);
		input = NULL;
		if (token)
			free(token);
		token = NULL;
	}
	clear_token_list(&token_list);
	write_history(".my_history");
	return (0);
}
