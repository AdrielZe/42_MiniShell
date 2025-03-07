/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exitcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:32:09 by victda-s          #+#    #+#             */
/*   Updated: 2025/03/06 20:40:24 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	add_exitcode(int status)
{
	char	*status_char;

	status_char = ft_itoa(status);
	if(!status_char)
		return ;
	setenv("EXITCODEMINISHELL", status_char, 1);
	free(status_char);
	
}