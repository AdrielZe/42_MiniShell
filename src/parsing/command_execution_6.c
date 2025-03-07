/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:17:45 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/28 17:51:31 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	search_for_cmd_in_array(t_ast_node *node, char **temp,
			char ***arr_not_envp, char **arr)
{
	*temp = "";
	*arr_not_envp = ft_split(node->value, ' ');
	if (!*arr_not_envp)
		return ;
	process_local_array(temp, *arr_not_envp);
	free_array(*arr_not_envp, array_len(*arr_not_envp));
}

void	handle_not_found_env_var(t_ast_node *node, char **envp, char **arr)
{
	char	*temp;
	char	**arr_not_envp;
	char	**value_to_search;

	search_for_cmd_in_array(node, &temp, &arr_not_envp, arr);
	if (temp == NULL || ft_strcmp(temp, "") == 0)
		return ;
	update_node_value(node, temp);
	free(temp);
	value_to_search = ft_split(node->value, ' ');
	process_valid_path(node, value_to_search, envp);
}

int	is_only_spaces(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ')
			return (1);
		str++;
	}
	return (0);
}

void	close_pipefd(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}
