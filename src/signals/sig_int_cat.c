/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_int_cat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:54:35 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/17 05:10:29 by asilveir         ###   ########.fr       */
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
