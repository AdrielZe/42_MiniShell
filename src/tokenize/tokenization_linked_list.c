/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_linked_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:57:52 by marvin            #+#    #+#             */
/*   Updated: 2025/01/24 13:57:54 by marvin           ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	new_node->type = type;
	new_node->value = ft_strdup(value);
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

void	print_list(t_tokens *token_list)
{
	t_tokens	*current;

	current = token_list;
	if (!current)
		printf("Token list is empty\n");
	printf("Current value: %s\n", current->value);
	while (current)
	{
		printf("[%u -", current->type);
		printf(" %s]\n", current->value);
		current = current->next;
	}
}
