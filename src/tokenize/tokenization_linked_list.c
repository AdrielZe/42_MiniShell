/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_linked_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:32:27 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/20 17:18:16 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tokenize.h"

void	append_token(t_tokens **token_list, t_token_type type, char *value)
{
	t_tokens		*new_node;
	t_tokens		*current;

	current = *token_list;
	new_node = malloc(sizeof(t_tokens));
	if (!new_node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_node->type = type;
	new_node->value = value;
	if (!new_node->value)
	{
		perror("strdup");
		free(new_node);
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	if (!*token_list)
	{
		*token_list = new_node;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new_node;
}

char	*get_token_by_index(t_tokens *token_list, int index)
{
	int			i;
	t_tokens	*current;

	i = 0;
	current = token_list;
	while (current)
	{
		if (i == index)
			return (current->value);
		i++;
		current = current->next;
	}
	return (NULL);
}

void	print_list(t_tokens *token_list)
{
	t_tokens	*current;

	current = token_list;
	while (current)
	{
		printf("[%u -", current->type);
		printf(" %s]\n", current->value);
		current = current->next;
	}
}
// int	main(void)
// {
// 	t_tokens *token_list = NULL;
// 	// Testando append_token
// 	append_token(&token_list, TOKEN_REDIRECT_OUT, ">");
// 	append_token(&token_list, TOKEN_APPEND, ">>");
// 	// append_token(&token_list, TOKEN_HEREDOC, "<<");

// 	// Imprimindo a lista completa
// 	printf("Lista de tokens:\n");
// 	print_list(token_list);
// 	printf("\n");

// 	return 0;
// }
