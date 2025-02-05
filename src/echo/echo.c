/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:10:58 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/03 18:10:58 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"

void	echo(t_tokens *tokens)
{
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type == TOKEN_ENV_VAR)
		{
			tokens->value = process_env_var(tokens->value);
		}
		ft_putstr_fd(tokens->value, 1);
		ft_putstr_fd(" ", 1);
		tokens = tokens->next;
	}
	printf("\n");
}
