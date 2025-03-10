/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:52:25 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/09 17:52:25 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	control_quotes(const char *new_word)
{
	int	i;
	int	double_quotes_number;
	int	simple_quotes_number;
	int	in_single_quotes;
	int	in_double_quotes;

	i = 0;
	double_quotes_number = 0;
	simple_quotes_number = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;

	// Contagem das aspas e verificações para alternar entre aspas simples e duplas
	while (new_word[i])
	{
		if (new_word[i] == '\'')
		{
			// Se estiver fora de aspas duplas, alterna entre dentro e fora das aspas simples
			if (!in_double_quotes)
				in_single_quotes = !in_single_quotes;
		}
		if (new_word[i] == '"')
		{
			// Se estiver fora de aspas simples, alterna entre dentro e fora das aspas duplas
			if (!in_single_quotes)
				in_double_quotes = !in_double_quotes;
		}
		i++;
	}

	// Se houver um número ímpar de aspas (simples ou duplas) fora de outras aspas, retorna erro
	if (in_single_quotes || in_double_quotes)
	{
		if (in_single_quotes)
			printf("minishell: unexpected EOF for `\'\'\n");
		if (in_double_quotes)
			printf("minishell: unexpected EOF for `\"\"\n");
		return (1);
	}
	return (0);
}

