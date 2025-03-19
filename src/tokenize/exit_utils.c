/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:22:50 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 09:18:37 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	handle_exit_errors(char **args_array)
{
	if (array_len(args_array) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		write_exitcode(1);
		return (0);
	}
	if (array_len(args_array) > 1 && !ft_isnumeric(args_array[1]))
	{
		ft_putstr_fd("minishell exit: ", STDERR_FILENO);
		ft_putstr_fd(args_array[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	clean_exit(int exit_code, char **envp,
		t_tokens **token_list, t_ast_node *node)
{
	free_array(envp);
	if (node)
		free_ast(node);
	if (token_list)
		clear_token_list(token_list);
	rl_clear_history();
	clear_history();
	exit(exit_code);
}
