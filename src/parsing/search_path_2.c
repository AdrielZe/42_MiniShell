/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:27:34 by marvin            #+#    #+#             */
/*   Updated: 2025/02/27 23:11:50 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
int	cd(char *argv[]);
int	export(char *argv[], char **envp);

static int if_cd(char *cmd, char *tokens[], char **envp, t_ast_node *node)
{
	if (!tokens || !tokens[0])
		perror("Comando vazio\n");
	else if(ft_strcmp(tokens[0], "cd") == 0)
	{
		if(cd(tokens))
			return (1);
	}
	else if(ft_strcmp(tokens[0], "export") == 0)
	{
		if(export(tokens, envp))
			return (1);
	}
	if(node->outfile)
		close(node->outfile);
	if(node->infile)
		close(node->infile);
	return (0);
}
static void	valid_outfile_and_path(char *cmd, t_ast_node *node, char *path)
{
	if (!path)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(" :command not found\n", STDERR_FILENO);
		exit(127);
	}
}

static char    *if_env_var(t_ast_node *node, char **tokens)
{
    char    *cmd;
    char    *expanded;
    int		i;

    i = 0;
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
static void	execute_node_command(t_ast_node *node, char *cmd, char **envp)
{
	char	**tokens;
	char	*path;
	pid_t	pid;
	char	*built[1];
	char	**path_split;

	built[0] = "PATH=built-ins";
	tokens = split_with_quotes(cmd);
	cmd = if_env_var(node, tokens);
	if(if_cd(cmd, tokens, envp, node))
		return ;
	path = search_valid_path(ft_split(cmd, ' ')[0], built);
	if(!path)
	{
		path_split = ft_split(cmd, ' ');
		path = search_valid_path(path_split[0], envp);
		free_array(path_split, array_len(path_split));
	}
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		valid_outfile_and_path(cmd, node, path);
		if (execve(path, tokens, envp) == -1)
			exit (127);
		exit (0);
	}
	free(path);
	waitpid(pid, NULL, 0);
}

static void	execute_word_node(t_ast_node *node, char *cmd, char **envp)
{
	char	**tokens;
	char	*path;
	pid_t	pid;
	char	*built[1];

	built[0] = "PATH=built-ins";
	tokens = split_with_quotes(cmd);
	cmd = if_env_var(node, tokens);
	path = search_valid_path(ft_split(cmd, ' ')[0], built);
	if(!path)
		path = search_valid_path(ft_split(cmd, ' ')[0], envp);
	if(if_cd(cmd, tokens, envp, node))
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		valid_outfile_and_path(cmd, node, path);
		if (execve(path, tokens, envp) == -1)
			exit(127);
		exit(0);
	}
	waitpid (pid, NULL, 0);
}

void	execute_command(char *cmd, char **envp,
			t_ast_node *node)
{
	if (node->outfile)
		dup2(node->outfile, STDOUT_FILENO);
	if (node->infile)
		dup2(node->infile, STDIN_FILENO);
	if (node->type == NODE_COMMAND)
		execute_node_command(node, cmd, envp);
	else if (node->type == TOKEN_WORD)
		execute_word_node(node, cmd, envp);
}
