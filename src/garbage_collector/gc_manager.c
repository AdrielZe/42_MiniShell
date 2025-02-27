/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:12:05 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/27 16:12:09 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

static t_shell *g_shell = NULL;

void set_gc_shell(t_shell *shell)
{
	g_shell = shell;
}

t_shell *get_gc_shell(void)
{
	return (g_shell);
}
