/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:51:32 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/26 22:37:56 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	free_delimiters(t_delim *head)
{
	t_delim	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->delimiter)
			free(head->delimiter);
		free(head);
		head = tmp;
	}
}

t_delim	*get_all_delimiters(t_ast_node *node)
{
	t_delim	*head;
	t_delim	*new;
	char	**delim;

	head = NULL;
	if (node_exists(node) == 1)
	{
		printf("✘ minishell: syntax error near unexpected token `newline'\n");
		return (NULL);
	}
	while (node && node->type == NODE_HEREDOC)
	{
		new = malloc(sizeof(t_delim));
		if (!new)
			return (NULL);
		delim = ft_split(node->right->value, ' ');
		if (!delim)
			return (NULL);
		new->delimiter = ft_strdup(delim[0]);
		free_array(delim, array_len(delim));
		new->next = head;
		head = new;
		node = node->left;
	}
	return (head);
}

void	check_all_commands(t_ast_node *node, char **envp)
{
	char *cmd;

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		while (node->type != NODE_COMMAND)
			node = node->left;
		cmd = ft_strtrim(node->value, " ");
		if (search_valid_path(cmd, envp) == NULL)
		{
			printf("minishell: %s: command not found\n", cmd);
			free(cmd);
		}
		// add_exitcode(127);
	}
	check_all_commands(node->left, envp);
	check_all_commands(node->right, envp);
}
