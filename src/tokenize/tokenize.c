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

size_t ft_count_word(const char *s, char *c)
{
	size_t	count = 0;
	size_t pipe_count = 0;

	while (*s)
	{
		s += count_if(&count, s, c);
		while (*s && strchr(c, *s))
		{
			pipe_count++;
			s++;
		}
	}
	return (count + pipe_count);
}
			


static char *process_quotes(const char **s, char *c)
{
	const char	*start;
	char	quote;
	int	is_delim;
	int	i;

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
	else
	{
		start = *s;
		while (**s)
		{
			is_delim = 0;
			i = 0;
			while (c[i] != '\0')
			{
				if (**s == c[i]) 
				{
					is_delim = 1;
              			break;
                		}
				i++;
			}
			if (is_delim || **s == '"' || **s == '\'')
				break;
			(*s)++;
        }
        return (allocate_word(start, *s - start));
    }
}


char **tokenize(const char *s, char **c)
{
    int i;
    int j;
    char **array;
    int word_count;

    i = 0;
    j = 0;
    word_count = 0;

    while (c[j]) 
    {
        word_count += ft_count_word(s, c[j]);
        j++;
    }
	printf("%i\n", word_count);
    array = malloc((word_count + 1) * sizeof(char *));
    if (!array)
        return (NULL);

    j = 0;
    while (c[j]) 
    {
	printf("entrou\n");
        while (*s)
        {
            while (*s == ' ')
                s++;
            alloc_pipe(&s, &array, &i);
            alloc_heredoc(&s, &array, &i);
            array[i] = process_quotes(&s, c[j]);
            if (!array[i])
            {
                free_array(array, i);
                return (NULL);  
            }
            i++;
        }
        j++;
    }
    array[i] = NULL;
    return (array);
}


