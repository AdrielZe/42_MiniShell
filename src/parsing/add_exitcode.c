/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exitcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:32:09 by victda-s          #+#    #+#             */
/*   Updated: 2025/03/07 01:46:56 by marvin           ###   ########.fr       */
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