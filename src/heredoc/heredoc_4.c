/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:03:29 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/05 17:50:23 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	write_and_free_input(int *pipefd, char *input)
{
	write(pipefd[1], input, ft_strlen(input));
	write(pipefd[1], "\n", 1);
	free(input);
}

void	display_input_line(char **input, char **envp, t_ast_node *node)
{
	*input = readline("heredoc> ");
	if (!*input)
	{
		handle_ctrl_d_heredoc(envp, NULL, node);
		return ;
	}
}

int	node_exists(t_ast_node *node)
{
	if (!node || !node->right || !node->right->value
		|| ft_strcmp(node->right->value, " ") == 0)
	{
		printf("✘ minishell: syntax error near unexpected token `newline'\n");
		add_exitcode(2);
		return (1);
	}
	return (0);
}
