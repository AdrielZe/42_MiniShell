/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_regular_cmd_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:42:52 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 06:55:40 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <sys/stat.h>

int	not_result_msg_free(char *search_result,
			t_ast_node *node, char **split_values, char *command_to_execute)
{
	if (!search_result)
	{
		not_found_msg_and_free(node, search_result,
			split_values, command_to_execute);
		return (1);
	}
	return (0);
}
