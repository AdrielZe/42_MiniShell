/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:56:21 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/13 19:27:33 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	main(void)
{
	char	*input;
	char	**token;

	while (1)
	{
		input = readline("Digite algo> ");
		if (input == NULL)
		{
			printf("Saindo do programa.\n");
			break ;
		}
		token = tokenize(input, ' ');
	    printf("Tokens:\n");
		for (int i = 0; token[i] != NULL; i++) {
			printf("Token %d: %s\n", i + 1, token[i]);
			free(token[i]);
		}
		// printf("%s\n", process_env_var(input));
		if (*input)
			add_history(input);
		free(input);
	}
	write_history(".my_history");
	return (0);
}
