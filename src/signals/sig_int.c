/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:49:18 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/28 18:01:59 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

void handle_sigint(int sig)
{
    (void)sig;

    // Limpa a linha e não coloca nada
    rl_replace_line("", 0);
    rl_on_new_line();  // Mover o cursor para uma nova linha
    rl_redisplay();    // Atualiza a tela

    // Exibe o prompt
    write(1, "\n> ", 3);  // Exibe o prompt novamente
}

void	handle_ctrl_d(char **envp_copy, t_tokens **token_list, t_ast_node *root)
{
	write(1, "Exiting minishell\n", 19);
		free_ast(root);
	clear_token_list(token_list);
	free_array(envp_copy, array_len(envp_copy));
	rl_clear_history();
	clear_history();
	exit(0);
}
