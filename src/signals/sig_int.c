/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:49:18 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/27 21:03:58 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	write(1, "> ", 2);
}

void	handle_ctrl_d(char **envp_copy, t_tokens **token_list, t_ast_node *root)
{
	write(1, "Exiting minishell\n", 19);
	if (token_list && *token_list)
		clear_token_list(token_list);
	if (root)
		free_ast(root);
	if (envp_copy)
		free_array(envp_copy, array_len(envp_copy));
	rl_clear_history();
	clear_history();
	exit(0);
}
