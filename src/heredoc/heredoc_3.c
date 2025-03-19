/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:51:32 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/26 23:05:20 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

char	**map_strings(char **array, int size, char *(*func)(char *, int))
{
	char	*new_value;
	int		i;

	i = 0;
	new_value = NULL;
	if (!array || !func)
		return (NULL);
	while (i < size)
	{
		if (array[i][0] == '$')
		{
			new_value = func(array[i], 1);
			if (!new_value)
				return (NULL);
			array[i] = new_value;
		}
		i++;
	}
	return (array);
}

char	**replace_at_index(char **array, int size,
			int index, const char *new_value)
{
	if (index < 0 || index >= size)
		return (array);
	free(array[index]);
	array[index] = strdup(new_value);
	if (!array[index])
		return (NULL);
	return (array);
}

void	handle_nodes_to_execute_command(t_ast_node *current, int pipe_found,
		t_ast_node *node, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	while (current->type != NODE_COMMAND)
		find_command_node(node, &current, pipe_found, envp);
	while (current)
	{
		if (current->type == NODE_COMMAND && pipe_found == 0)
		{
			if (node->right->outfile)
				dup2(node->right->outfile, STDOUT_FILENO);
			if (pid == 0)
				exec_heredoc_cmds(node, current, envp);
		}
		else
			search_valid_path(ft_split(current->value, ' ')[0], envp);
		current = current->left;
	}
	waitpid(pid, &status, 0);
	check_all_commands(node, envp);
	cleanup_heredoc(node, envp);
	exit(1);
}

void	close_heredoc_prompt(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("here-document at line ", 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putendl_fd("')", 2);
}
