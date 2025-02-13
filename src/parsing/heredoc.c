/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:41:35 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/13 17:42:57 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	protect_fork(pid_t *pid)
{
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
}
void	check_all_commands(t_ast_node *node, char **envp)
{
	if (!node)
		return;
	

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

void	open_heredoc_pipe(int *pipefd, pid_t *pid)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	*pid = fork();
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
}

void	read_heredoc(int *pipefd, t_delim *delimiters)
{
	char	*input;
	t_delim *current;

	close(pipefd[0]);
	current = delimiters;
	while (current)
	{
		while (1)
		{
			input = readline("heredoc> ");
			if (!input)
				break;
			if (!ft_strcmp(input, current->delimiter))
			{
				free(input);
				current = current->next;
				break;
			}
			write(pipefd[1], input, ft_strlen(input));
			write(pipefd[1], "\n", 1);
			free(input);
		}
	}
	close(pipefd[1]);
	free_delimiters(delimiters);
	exit(0);
}

void	execute_command_with_heredoc(int *pipefd,
			pid_t pid, t_ast_node *node, char **envp)
{
	char	**args;
	t_ast_node	*current;
	int	pipe_found;

	current = node;
	args = malloc(2 * sizeof(char *));
	args[0] = node->left->value;
	args[1] = NULL;
	pipe_found = 0;
	search_valid_path(node->left->value, envp);
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	pid = fork();
	protect_fork(pipefd);
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		while (current->type != NODE_COMMAND)
		{
			current = current->left;
			if (current->type == NODE_PIPE && pipe_found == 0)
			{
				pipe_found = 1;
				execute_command(current->right->value, envp, node);
			}	
		}
		while (current)
		{
			if (current->type == NODE_COMMAND && pipe_found == 0)
			{
				execute_command(current->value, envp, node);
			}
			else
				search_valid_path(ft_split(current->value, ' ')[0], envp);
			current = current->left;
		}
		
		// if (current->type == NODE_HEREDOC && current->left->type == NODE_PIPE)
		// 	execute_command(current->left->right->value, envp, node);
		// else 
		// {
		// 	execute_command(current->left->value, envp, node);
		// }
		check_all_commands(node, envp);
		exit(1);
	}

	close(pipefd[0]);
	waitpid(pid, NULL, 0);
}


void	print_delim_list(t_delim *delim_list)
{
	t_delim	*current = delim_list;
	int		index = 1;

	if (!current)
	{
		printf("Lista de delimitadores vazia.\n");
		return;
	}
	while (current)
	{
		current = current->next;
		index++;
	}
}

t_delim *get_all_delimiters(t_ast_node *node)
{
	t_delim	*head = NULL;
	t_delim	*new;

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



void	handle_heredoc(t_ast_node *node, char **envp)
{
	pid_t	pid;
	int	pipefd[2];
	t_delim	*delim_list;

	//current = node;
	open_heredoc_pipe(pipefd, &pid);
	if (pid == 0)
	{
		delim_list = get_all_delimiters(node);
		read_heredoc(pipefd, delim_list);
	}
	execute_command_with_heredoc(pipefd, pid, node, envp);
}

