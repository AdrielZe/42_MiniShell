/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:59:58 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/15 12:10:25 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../headers/main.h"

void	free_array(char **array, int i)
{
	while (i-- > 0)
		free(array[i]);
	free(array);
}

char	*allocate_word(const char *s, int len)
{
	char	*word;

	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	strncpy(word, s, len);
	word[len] = '\0';
	return (word);
}

size_t	ft_count_word(const char *s, char c)
{
	size_t	count;
	char	quote;

	count = 0;
	while (*s)
	{
		if (*s == '"' || *s == '\'')
		{
			quote = *s++;
			while (*s && *s != quote)
				s++;
			if (*s)
				s++;
			count++;
		}
		else if (*s++ == '|')
			count++;
		else
		{
			while (*s && *s != c && *s != '|' && *s != '"' && *s != '\'')
				s++;
			count++;
		}
		while (*s == c)
			s++;
	}
	return (count);
}

static char	*process_quotes(const char **s, char c)
{
	const char	*start;
	char		quote;

	if (**s == '"' || **s == '\'')
	{
		quote = **s;
		start = (*s)++;
		while (**s && **s != quote)
			(*s)++;
		if (**s)
			(*s)++;
		return (allocate_word(start, *s - start));
	}
	else if (**s == '|')
		return (allocate_word((*s)++, 1));
	else
	{
		start = *s;
		while (**s && **s != c && **s != '|' && **s != '"' && **s != '\'')
			(*s)++;
		return (allocate_word(start, *s - start));
	}
}

char	**tokenize(const char *s, char c)
{
	int		i;
	char	**array;

	i = 0;
	array = malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			array[i] = process_quotes(&s, c);
			if (!array[i])
			{
				free_array(array, i);
				return (NULL);
			}
			i++;
		}
	}
	array[i] = NULL;
	return (array);
}

// int main() {
//     char str[] = " Teste de Funcionamento  ok ";
//     char delimiter = ' ';
//     char **result = ft_split(str, delimiter);
//     if (!result) {
//         printf("Erro ao alocar memória.\n");
//         return (1);
//     }
//     printf("Tokens:\n");
//     for (int i = 0; result[i] != NULL; i++) {
//         printf("Token %d: %s\n", i + 1, result[i]);
//         free(result[i]);
//     }
//     free(result);
//     return (0);
// }