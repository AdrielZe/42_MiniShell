/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:59:58 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/29 16:03:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include "../../headers/parsing.h"

void	free_array(char **array, int i)
{
	if (!array)
		return ;
	while (i-- > 0)
	{
		if (array[i])
			free(array[i]);
	}
	free(array);
}

char	*allocate_word(const char *s, int len)
{
	char	*word;

	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, s, len);
	word[len] = '\0';
	return (word);
}

size_t	ft_count_word(const char *s)
{
	size_t	count;
	size_t	delim_counter;

	delim_counter = 0;
	count = 0;
	while (*s)
	{
		s += count_if(&count, s);
		while (*s == '|' || (*s == '<' && *(s + 1) == '<'))
		{
			delim_counter++;
			s++;
			if (*s)
				s++;
		}
		count++;
	}
	return (count + delim_counter);
}

static char	*process_quotes(const char **s)
{
	const char	*start;
	char		quote;

	start = *s;
	if (**s == '"' || **s == '\'')
	{
		quote = *(*s)++; // Captura a aspa inicial e avança
		while (**s && **s != quote)
			(*s)++;
		if (**s == quote) // Se encontrar a aspa final, avança novamente
			(*s)++;
	}
	else if (**s == '|') // Se for pipe, apenas avança um caractere
		(*s)++;
	else
	{
		while (**s && **s != '|' && **s != '<' && **s != '>' 
			&& **s != '"' && **s != '\'')
			(*s)++;
	}

	// Aloca a palavra corretamente, considerando os caracteres percorridos
	return (allocate_word(start, *s - start));
}


char	**tokenize(const char *s)
{
	int		i;
	char	**array;
	char	*new_word;
	int	is_string;
	char	*new_str;

	i = 0;
	is_string = 0;
	array = malloc((ft_count_word(s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*s)
	{
		skip_spaces_and_alloc_elements(&s, &array, &i);
		if (*s == '\0')
			break ;
		new_word = process_quotes(&s);
		if (!new_word)
			return (free_array(array, i), NULL);
		int len = ft_strlen(new_word);
		if ((new_word[0] == '"' || new_word[0] == '\'') && new_word[len - 1] == new_word[0] && len > 1)
		{
			new_str = ft_substr(new_word, 1, len - 2); // Remove primeira e última aspas
			is_string = 1;
			printf("new_str: %s\n", new_str);

		}
		new_word = remove_quotes(new_word);
		if (should_merge_token(array, i, is_string, new_word) == 1)
			merge_last_token(&array, i, new_word);
		else
			alloc_new_word_in_array(&array, &i, new_word);
	}
	array[i] = NULL;
	return (array);
}
