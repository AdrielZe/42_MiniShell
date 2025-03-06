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

void check_if_is_string(char *new_word, char **old_string, int *is_string, int len)
{
    char quote_type = 0;

    if (*is_string && *old_string)
        quote_type = (*old_string)[0];


	if (ft_strlen(new_word) > 1 && (new_word[0] == '\''
			&& new_word[ft_strlen(new_word) - 1] == '\'') ||
			(new_word[0] == '"'
			&& new_word[ft_strlen(new_word) - 1] == '"'))
	{
		printf("ENTROU AQUI\n");
		*is_string = 1;
	}
    if (*old_string)
        free(*old_string);
    *old_string = ft_strdup(new_word);
}

void process_words(const char **s, char ***array, int *i) {
    char *old_string = NULL;
    char *new_word;
    int is_string;
    int len;

    is_string = 0;
    old_string = NULL;
    while (**s) {
        skip_spaces_and_alloc_elements(s, array, i);
        if (*s == NULL)
            break;
        get_new_word(&new_word, s, array, i);
        len = ft_strlen(new_word);

        // Verifica se o token é uma string
        check_if_is_string(new_word, &old_string, &is_string, len);

        // Se for o primeiro elemento do array, não faz merge, apenas aloca
        if (*i == 0) {
            printf("First element, alloc in array\n");
            printf("NEW WORD: %s\n", new_word);
            alloc_new_word_in_array(array, i, new_word, &old_string);
		is_string = 0;
        }
        // Caso contrário, verifica se deve fazer merge ou alocar
        else if (should_merge_token(*array, *i, is_string) == 1) {
            printf("new word: %s IS string\n", new_word);
            merge_last_token(array, *i, new_word);
            is_string = 0;
            old_string = NULL;
        } else {
            printf("alloc in array\n");
            printf("NEW WORD: %s\n", new_word);
            alloc_new_word_in_array(array, i, new_word, &old_string);
        }

        free(old_string);
    }
}
