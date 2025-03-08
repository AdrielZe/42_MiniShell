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

static void	get_new_word(char **new_word, const char **s, char ***array, int *i)
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

void	check_if_is_string(char *new_word, char **old_string, int *is_string)
{
	if ((ft_strlen(new_word) > 1 &&
		((new_word[0] == '\'' && new_word[ft_strlen(new_word) - 1] == '\'') ||
		(new_word[0] == '"' && new_word[ft_strlen(new_word) - 1] == '"'))))
		*is_string = 1;
	
	*old_string = new_word;
	if(*old_string == NULL)
	{
		perror("ft_strdup failed");
		exit(EXIT_FAILURE);
	}
}

#include <stdio.h>

void remove_quotes(char *str)
{
    char *read = str;
    char *write = str;

    while (*read)
    {
        // Se o caractere não for uma aspa, copie-o para a posição de 'write'
        if (*read != '"' && *read != '\'')
        {
            *write = *read;
            write++;
        }
        read++;
    }
    *write = '\0';  // Finaliza a string
}



void	process_words(const char **s, char ***array, int *i, char **envp) 
{
	char *old_string;
	char *new_word;
	int is_string;
	static int	is_executable;	

	is_string = 0;
	old_string = NULL;
	while (**s)
	{
		skip_spaces_and_alloc_elements(s, array, i);
		if (*s == NULL)
			break;
		get_new_word(&new_word, s, array, i);
		check_if_is_string(new_word, &old_string, &is_string);
		if (*i == 0) 
		{
			alloc_new_word_in_array(array, i, new_word, &old_string);
			is_string = 0;
		}
		else if (should_merge_token(is_string) == 1 || is_executable == 1)
		{
			merge_last_token(array, *i, new_word);
			is_string = 0;
			is_executable = 0;
			old_string = NULL;
		} else 
			alloc_new_word_in_array(array, i, new_word, &old_string);
		remove_quotes(new_word);
		if (search_valid_path(new_word, envp) != NULL)
		{
			printf("is executable: %s\n", new_word);
			is_executable = 1;
		}
	}
	if (old_string)
		free(old_string);
}
