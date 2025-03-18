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

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
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
		while (*s == '|')
		{
			delim_counter++;
			if (*s)
				s++;
		}
		count++;
	}
	return (count + delim_counter);
}

int	is_quoted(const char *s)
{
	char	**cmd_split;
	int		len;

	len = 0;
	if (!s)
	{
		printf("Error: s is NULL\n");
		return (0);
	}
	if (s[0] == '"' || s[0] == '\'')
		return (s[0]);
	return (0);
}

int	check_pipe_syntax(const char *s)
{
	int	prev_char_was_pipe;

	prev_char_was_pipe = 0;
	while (*s == ' ')
		s++;
	if (*s == '\0')
		return (1);
	if (*s == '|')
		return (1);
	while (*s)
	{
		if (*s == '|')
		{
			if (prev_char_was_pipe)
				return (1);
			s++;
			while (*s == ' ')
				s++;
			if (*s == '\0')
				return (1);
			prev_char_was_pipe = 1;
		}
		else
		{
			prev_char_was_pipe = 0;
			s++;
		}
	}
	return (0);
}

char	**tokenize(const char *s, char **envp)
{
	char	**array;
	char	*s_copy;
	int		i;

	i = 0;
	while (*s && *s == ' ')
		s++;
	if (s == NULL || ft_count_word(s) == 0)
		return (NULL);
	s_copy = ft_strdup(s);
	if (control_syntax(s_copy, array) == 1)
		return (NULL);
	array = ft_calloc(ft_count_word(s) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	process_words(&s, &array, &i, envp);
	free(s_copy);
	array[i] = NULL;
	return (array);
}
