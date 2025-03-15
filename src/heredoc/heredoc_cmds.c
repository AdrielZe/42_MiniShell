/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:09:05 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/14 19:40:51 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

t_heredoc_data	*get_heredoc_data(void)
{
	static t_heredoc_data	data = {NULL, NULL};

	return (&data);
}

void	find_command_node(t_ast_node *node,
		t_ast_node **current, int pipe_found, char **envp)
{
	*current = (*current)->left;
	if ((*current)->type == NODE_PIPE && pipe_found == 0)
	{
		pipe_found = 1;
		if (node->right->outfile)
			dup2(node->right->outfile, STDOUT_FILENO);
		execute_command((*current)->right->value, envp, node);
	}
}

void	exec_heredoc_cmds(t_ast_node *node, t_ast_node *current, char **envp)
{
	char	*string;
	char	**args;
	char	**value_splitted;
	char	*value;

	string = node->right->value;
	args = split_with_quotes(string);
	printf("node value %s\n", node->value);
	value_splitted = ft_split(current->value, ' ');
	value = search_valid_path(value_splitted[0], envp);
	args = replace_at_index(args, array_len(args), 0, value_splitted[0]);
	args = map_strings(args, array_len(args), process_env_var);
	free (value_splitted);
	if (execve(value, args, envp) == -1)
	{
		perror("execve\n");
		exit(2);
	}
}
