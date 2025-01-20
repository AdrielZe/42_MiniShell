/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:56:21 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/20 17:16:15 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include "../headers/tokenize.h"


int	main(void)
{
	char		*input;
	char		**token;
	t_tokens	*token_list;

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
		printf("Lista de tokens:\n");
		classify_token(token, &token_list);
		printf("[%s]\n", get_token_by_index(token_list, 1));
		//print_list(token_list);
		// printf("Tokens:\n");
		// printf("%s", input);
		// printf("%s\n", process_env_var(input));
		if (*input)
			add_history(input);
		free(input);
		input = NULL;
	}
	clear_token_list(&token_list);
	write_history(".my_history");
	return (0);
}
