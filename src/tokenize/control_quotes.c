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

int	inside_quotes(int in_single_quotes, int in_double_quotes)
{
	if (in_single_quotes || in_double_quotes)
	{
		if (in_single_quotes)
			printf("minishell: unexpected EOF for `\"\"\n");
		if (in_double_quotes)
			printf("minishell: unexpected EOF for `\'\'\n");
		return (1);
	}
	return (0);
}

void	start_variables(int *double_quotes_number, int *simple_quotes_number,
	int *in_single_quotes, int *in_double_quotes)
{
	*double_quotes_number = 0;
	*simple_quotes_number = 0;
	*in_single_quotes = 0;
	*in_double_quotes = 0;
}

int	control_quotes(const char *new_word)
{
	int	i;
	int	in_single_quotes;
	int	in_double_quotes;
	int	double_quotes_number;
	int	simple_quotes_number;

	i = 0;
	start_variables(&double_quotes_number, &simple_quotes_number,
		&in_single_quotes, &in_double_quotes);
	while (new_word[i])
	{
		if (new_word[i] == '\'')
		{
			if (!in_double_quotes)
				in_single_quotes = !in_single_quotes;
		}
		if (new_word[i] == '"')
			if (!in_single_quotes)
				in_double_quotes = !in_double_quotes;
		i++;
	}
	if (inside_quotes(in_double_quotes, in_single_quotes) == 1)
		return (1);
	return (0);
}

void	add_quote_type(char **s, char quote)
{
	char	*quoted_str;
	int		len;

	if (!s || !*s)
		return ;
	len = ft_strlen(*s) + 2;
	quoted_str = malloc(len + 1);
	if (!quoted_str)
		return ;
	quoted_str[0] = quote;
	ft_strcpy(quoted_str + 1, *s);
	quoted_str[len - 1] = quote;
	quoted_str[len] = '\0';
	free(*s);
	*s = quoted_str;
}
