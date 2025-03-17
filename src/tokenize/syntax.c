/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:53:40 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/17 13:00:50 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	control_syntax(char *s_copy, char **array)
{
	if (check_pipe_syntax(s_copy))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		free(s_copy);
		return (1);
	}
	if (control_quotes(s_copy) == 1)
		return (1);
	if (is_only_dollar(s_copy) == 0)
	{
		array = split_with_quotes(s_copy);
		printf("minishell: %s: command not found\n", array[0]);
		free_array(array);
		free(s_copy);
		return (1);
	}
	return (0);
}
