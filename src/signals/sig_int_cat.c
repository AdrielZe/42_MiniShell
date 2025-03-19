/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_int_cat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:54:35 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/19 09:09:11 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	sigint_cat_action(int sig)
{
	(void)sig;
	signal(SIGQUIT, sigquit_handler);
	ft_putchar_fd('\n', 1);
	return ;
}

void	sigquit_handler(int sig)
{
	(void)sig;
}

void	handle_ctrl_d_heredoc(char **envp_copy,
	t_tokens **token_list, t_ast_node *root)
{
	cleanup_heredoc(root, envp_copy);
	clear_token_list(token_list);
	token_list = NULL;
	rl_clear_history();
	clear_history();
	exit(0);
}

void	sigint_heredoc_action(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	exit(130);
}
