/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:56:21 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/23 12:47:22 by victda-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../headers/main.h"
#include "../headers/tokenize.h"
#include "../headers/parsing.h"



int	main(void)
{
	char		*input;
	char		**token;
	t_tokens	*token_list;
	t_ast_node *root;

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
		{
			echo(token_list);
		}
		else
		{

		// printf("[%s]\n", get_token_by_index(token_list, 1));
		printf("Lista de tokens:\n");
		root = build_ast(token_list);
		printf(" RESULT: %s\n", parse_commands(root));
		//print_list(token_list);
		// printf("Tokens:\n");
		// printf("%s", input);
		// printf("%s\n", process_env_var(input));
		}
		if (*input)
			add_history(input);
		free(input);
		input = NULL;
		if(token)
			free(token);
		token = NULL;
	}
	clear_token_list(&token_list);
	write_history(".my_history");
	return (0);
}
