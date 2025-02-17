/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:49:18 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/16 23:00:45 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	handle_sigint(int sig)
{
	write(1, "\n", 1);
	write(1, "Digite algo> ", 13);
}

void	handle_ctrl_d(int sig)
{
	write(1, "Exiting minishell\n", 19);
	exit(0);
}


