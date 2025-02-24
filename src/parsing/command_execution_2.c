/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/24 15:04:50 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <sys/stat.h>

int is_directory(char *path)
{
	struct stat path_stat;
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}


int is_file(const char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) != 0)
        return (0);

    return (S_ISREG(path_stat.st_mode));
}

static void	handle_command_node(t_ast_node *node, char **envp)
{
	char	old_char;
	char *old_string;

	if (!node->value || node->value[0] == '\0')
		return ;
	old_char = node->value[0];
	old_string = ft_strdup(node->value);
	node->value = process_env_var(node->value);
	
}

static void	when_only_env_var(t_ast_node *node, char **envp, char *old_string)
{
	if (is_directory(node->value))
	{
		printf("minishell: %s: Is a directory\n", node->value);
		return;
	}
	if (!is_file(node->value) && !search_valid_path(node->value, envp))
	{
		if (ft_strcmp(old_string, node->value) != 0)
			printf("zsh: %s: No such file or directory\n", node->value);
		else
			return ;
		return ;
	}
	execute_command(node->value, envp, node, 1);
}

static void check_if_is_cmd(t_ast_node *node, char **envp)
{
	if (ft_split(node->value, ' ')[0])
	{
		if (search_valid_path(ft_split(node->value, ' ')[0], envp) == NULL)
		{
			printf("minishell: %s: command not found\n", ft_split(node->value, ' ')[0]);
			return ;
		}
	}
	if (is_directory(node->value))
	{
		printf("minishell: %s: Is a directory\n", node->value);
		return;
	} else 
		execute_command(node->value, envp, node, 0);
}

void handle_node_types(t_ast_node *node, char **envp, t_delim **delimiters)
{
	char	old_char;
	char	*old_string;
	if (node->type == NODE_HEREDOC)
	{
		*delimiters = get_all_delimiters(node);
		handle_heredoc(node, envp);
	}
	else if (node->type == NODE_COMMAND)
	{
		old_char = node->value[0];
		if (!node->value || node->value[0] == '\0')
			return ;
		old_string = ft_strdup(node->value);
		node->value = process_env_var(node->value);

		if (old_char == '$')
			when_only_env_var(node, envp, old_string);
		else if (ft_strcmp(old_string, node->value) != 0)
			check_if_is_cmd(node, envp);
		else
		{
			if (ft_strchr(node->value, '$') != NULL)
				execute_command(ft_split(node->value, ' ')[0], envp, node, 0);
			else
				execute_command(node->value, envp, node, 0);
		}
	}
}

