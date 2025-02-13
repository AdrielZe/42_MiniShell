/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:51:32 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/13 18:43:17 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	free_delimiters(t_delim *head)
{
	t_delim	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->delimiter);
		free(tmp);
	}
}

t_delim	*create_delim_list(char **delims)
{
	t_delim	*head;
	t_delim	*new;
	t_delim	*last;
	int		i;

	i = 0;
	head = NULL;
	last = NULL;
	while (delims[i])
	{
		new = malloc(sizeof(t_delim));
		if (!new)
			return (NULL);
		new->delimiter = strdup(delims[i]);
		new->next = NULL;
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return (head);
}

t_delim	*get_all_delimiters(t_ast_node *node)
{
	t_delim	*head;
	t_delim	*new;

	head = NULL;
	while (node && node->type == NODE_HEREDOC)
	{
		new = malloc(sizeof(t_delim));
		if (!new)
			return (NULL);
		new->delimiter = strdup(ft_split(node->right->value, ' ')[0]);
		new->next = head;
		head = new;
		node = node->left;
	}
	return (head);
}

void	check_all_commands(t_ast_node *node, char **envp)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		while (node->type != NODE_COMMAND)
			node = node->left;
		if (!search_valid_path(node->value, envp))
			printf("command not found: %s\n", node->value);
	}
	check_all_commands(node->left, envp);
	check_all_commands(node->right, envp);
}
