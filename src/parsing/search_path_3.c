/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:27:56 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/05 23:41:37 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

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

void	setup_tokens_and_commands(t_ast_node *node, char ***tokens,
		char **cmd, char ***cmd_to_split)
{
	*tokens = split_with_quotes(*cmd);
	*cmd = if_env_var(node, *tokens);
	*cmd_to_split = ft_split(*cmd, ' ');
	if (!*cmd_to_split)
		return ;
}

void	open_pid(int *pid)
{
	*pid = fork();
	if (*pid < 0)
		return ;
}
