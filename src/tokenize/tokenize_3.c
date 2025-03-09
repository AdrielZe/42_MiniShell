/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:49:40 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/27 21:22:26 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include "../../headers/parsing.h"

void	get_new_word(char **new_word, const char **s, char ***array, int *i)
{
	*new_word = process_quotes(s);
	if (!*new_word)
	{
		free_array(*array, *i);
		exit(0);
	}
}

void	print_array(char **array)
{
	int	j;

	j = 0;
	printf("Array atual:\n");
	if (!array)
	{
		printf("Array é NULL\n");
		return ;
	}
	while (array[j])
	{
		printf("[%d] %s\n", j, array[j]);
		j++;
	}
	printf("\n");
}

int	count_quotes(char *new_word)
{
	int	i;
	int	double_quotes_number;
	int 	simple_quotes_number;
	
	i = 0;
	double_quotes_number = 0;
	simple_quotes_number = 0;
	while(new_word[i])
	{
		if (new_word[i] == '\'')
			simple_quotes_number++;
		if (new_word[i] == '"')
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

void	check_if_is_string(char *new_word, char **old_string, int *is_string)
{
	if ((ft_strlen(new_word) > 1 && ((new_word[0] == '\''
					&& new_word[ft_strlen(new_word) - 1] == '\'')
				|| (new_word[0] == '"'
					&& new_word[ft_strlen(new_word) - 1] == '"'))))
		*is_string = 1;
	*old_string = new_word;
	if (*old_string == NULL)
	{
		perror("ft_strdup failed");
		exit(EXIT_FAILURE);
	}
}

void	remove_quotes(char *str)
{
	char	*read;
	char	*write;

	read = str;
	write = str;
	while (*read)
	{
		if (*read != '"' && *read != '\'')
		{
			*write = *read;
			write++;
		}
		read++;
	}
	*write = '\0';
}

void	process_words(const char **s, char ***array, int *i, char **envp)
{
	char		*old_string;
	char		*new_word;
	static int	is_executable = 0;
	t_word_data	data;

	set_word_data(&data, old_string, is_executable, i);
	data.array = array;
	old_string = NULL;
	new_word = NULL;
	while (**s)
	{
		skip_spaces_and_alloc_elements(s, array, i);
		if (*s == NULL)
			break ;
		get_new_word(&new_word, s, array, i);
		if (count_quotes(new_word) != 0)
			break;
		if (!new_word)
		{
			free_array(*array, array_len(*array));
			return ;
		}
		process_new_word(new_word, &data);
		handle_word_quotes(new_word, &is_executable, envp, *i);
	}
	free(old_string);
}
