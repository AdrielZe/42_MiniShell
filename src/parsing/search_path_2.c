/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:27:34 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 16:26:37 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	valid_outfile_and_path(char *cmd, t_ast_node *node, char *path)
{
	if (!path)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(" :command not found\n", STDERR_FILENO);
		exit(127);
	}
}

char	*if_env_var(t_ast_node *node, char **tokens)
{
	char	*cmd;
	char	*expanded;
	int		i;

	i = 0;
	if (!tokens || !tokens[0])
		return (NULL);
	cmd = process_env_var(tokens[0]);
	if (node->type == NODE_ENV_VAR)
	{
		while (tokens[i])
		{
			if (ft_strchr(tokens[i], '$') != NULL)
			{
				expanded = process_env_var(tokens[i]);
				break ;
			}
			i++;
		}
		return (expanded);
	}
	return (cmd);
}

char	**prepare_command(t_ast_node *node, char *cmd, char **out_cmd)
{
	char	**tokens;

	tokens = split_with_quotes(cmd);
	if (!tokens)
		return (NULL);
	if (node->type != NODE_SIMPLE_QUOTE)
	{
		*out_cmd = if_env_var(node, tokens);
		if (!*out_cmd)
		{
			free_array(tokens, array_len(tokens));
			return (NULL);
		}
	}
	else
		*out_cmd = cmd;
	return (tokens);
}

void	execute_node_command(t_ast_node *node, char *cmd, char **envp)
{
	char	**tokens;
	char	*path;
	char	*updated_cmd;

	tokens = prepare_command(node, cmd, &updated_cmd);
	if (!tokens)
		return ;
	path = resolve_path(updated_cmd, envp);
	if (!path)
	{
		free_array(tokens, array_len(tokens));
		return ;
	}
	execute_command_for_node_function(path, tokens, envp, node);
	free(path);
	free_array(tokens, array_len(tokens));
}

void	execute_word_node(t_ast_node *node, char *cmd, char **envp)
{
	char	**tokens;
	char	*path;
	pid_t	pid;
	char	**cmd_to_split;
	char	*built[1];

	built[0] = "PATH=built-ins";
	setup_tokens_and_commands(node, &tokens, &cmd, &cmd_to_split);
	path = search_valid_path(cmd_to_split[0], built);
	if (!path)
		path = search_valid_path(cmd_to_split[0], envp);
	free_array(cmd_to_split, array_len(cmd_to_split));
	open_pid(&pid);
	if (pid == 0)
	{
		valid_outfile_and_path(cmd, node, path);
		if (execve(path, tokens, envp) == -1)
			exit(127);
		exit(0);
	}
	free(path);
	free_array(tokens, array_len(tokens));
	waitpid (pid, NULL, 0);
}
