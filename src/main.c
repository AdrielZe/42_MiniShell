/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:56:21 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/13 10:56:50 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("Digite algo> ");
		if (input == NULL)
		{
			printf("Saindo do programa.\n");
			break ;
		}
		printf("%s\n", process_env_var(input));
		if (*input)
			add_history(input);
		free(input);
	}
	write_history(".my_history");
	return (0);
}
