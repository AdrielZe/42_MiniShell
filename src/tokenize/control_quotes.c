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
	const	char *word_without_spaces;

	i = 0;
	double_quotes_number = 0;
	simple_quotes_number = 0;
	word_without_spaces = ft_strtrim(new_word, " ");
	if (word_without_spaces[0] == '\'' && word_without_spaces[ft_strlen(word_without_spaces) - 1] == '\'')
		return (0);
	while (word_without_spaces[i])
	{
		if (word_without_spaces[i] == '\'')
			simple_quotes_number++;
		if (word_without_spaces[i] == '"')
			double_quotes_number++;
		i++;
	}
	if ((simple_quotes_number % 2) != 0 || (double_quotes_number % 2) != 0)
	{
		if ((simple_quotes_number % 2) != 0)
			printf("minishell: unexpected EOF for `''\n");
		else
			printf("minishell: unexpected EOF for `\"'\n");
		return (1);
	}
	return (0);
}