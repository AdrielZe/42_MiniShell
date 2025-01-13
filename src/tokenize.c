/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:59:58 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/13 19:50:29 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	free_array(char **array, int i)
{
	while (i > 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

char	*allocate_word(const char *s, int len)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

size_t	ft_count_word(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == '|')
		{
			count++;
			s++;
		}
		else
		{
			while (*s && *s != c && *s != '|')
				s++;
			count++;
		}
		while (*s == c)
			s++;
	}
	return (count);
}

char	**tokenize(const char *s, char c)
{
	int			i;
	char		**array;
	const char	*start;

	i = 0;
	array = malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*s)
	{
		if (*s == '|')
			array[i++] = allocate_word(s++, 1);
		else
		{
			start = s;
			while (*s && *s != c && *s != '|')
				s++;
			array[i] = allocate_word(start, s - start);
			i++;
		}
		while (*s == c)
			s++;
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