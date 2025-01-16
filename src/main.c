/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:56:21 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/15 21:09:20 by victda-s         ###   ########.fr       */
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
		if (input == NULL)
		{
			printf("Saindo do programa.\n");
			break ;
		}
		token = tokenize(input, ' ');
		printf("Lista de tokens:\n");
		classify_token(token, token_list);
		// print_list(token_list);
		// printf("Tokens:\n");
		// for (int i = 0; token[i] != NULL; i++) {
		// 	printf("Token %d: %s\n", i + 1, token[i]);
		// 	free(token[i]);
		// }
		// printf("%s", input);
		// printf("%s\n", process_env_var(input));
		if (*input)
			add_history(input);
		free(input);
		input = NULL;
	}
	write_history(".my_history");
	return (0);
}
