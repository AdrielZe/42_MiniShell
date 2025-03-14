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

char **map_strings(char **array, int size, char *(*func)(char *, int))
{
	char *new_value;
	new_value = NULL;
	if (!array || !func)
		return NULL;

	for (int i = 1; i < size; i++)
	{
		if (array[i][0] == '$')
		{
			new_value = func(array[i], 0);
			if (!new_value)
				return NULL;
			free(array[i]);
			array[i] = new_value;
		}
	}
	return array;
}

char **replace_at_index(char **array, int size, int index, const char *new_value)
{
    if (index < 0 || index >= size) // Verifica se o índice é válido
        return array;

    free(array[index]);              // Libera a string antiga
    array[index] = strdup(new_value); // Substitui pela nova string
    if (!array[index])                // Verifica se a alocação falhou
        return NULL;

    return array;
}


void	handle_nodes_to_execute_command(t_ast_node *current, int pipe_found,
		t_ast_node *node, char **envp)
{
	pid_t pid;
	pid = fork();
	int status;
	while (current->type != NODE_COMMAND)
	{
		current = current->left;
		if (current->type == NODE_PIPE && pipe_found == 0)
		{
			pipe_found = 1;
			if (node->right->outfile)
				dup2(node->right->outfile, STDOUT_FILENO);
			execute_command(current->right->value, envp, node);
		}
	}
	while (current)
	{
		int new_size = 0;
		if (current->type == NODE_COMMAND && pipe_found == 0)
		{
			if (node->right->outfile)
				dup2(node->right->outfile, STDOUT_FILENO);
			if (pid == 0)
			{
				char *string = node->right->value;
				char **args = split_with_quotes(string);
				char **value_splitted = ft_split(current->value, ' ');
				char *value = search_valid_path(value_splitted[0], envp);
				args = replace_at_index(args, array_len(args), 0, value_splitted[0]);
				args = map_strings(args, array_len(args), process_env_var);
				free (value_splitted);
				if(execve(value, args, envp) == -1)
				{
					perror("execve\n");
					exit(2);
				}
			}
		}
		else
		search_valid_path(ft_split(current->value, ' ')[0], envp);
		current = current->left;
	}
	waitpid(pid, &status, 0);
	check_all_commands(node, envp);
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
