/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_linked_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:32:27 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/15 16:48:11 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tokenize.h"

void	append_token(t_tokens **token_list, t_token_type type, char *value)
{
	t_tokens		*new_node;
	t_tokens		*current;
	t_token_type	new_token_type;

	current = *token_list;
	new_token_type = type;
	new_node = malloc(sizeof(t_tokens));
	if (!new_node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_node->type = new_token_type;
	new_node->value = value;
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

void	print_list(t_tokens *token_list)
{
	t_tokens	*current;

	current = token_list;
	while (current)
	{
		printf("[%u -", current->type);
		printf(" %s]", current->value);
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
