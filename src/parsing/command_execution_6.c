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

void	search_for_cmd_in_array(t_ast_node *node,
				char **temp, char ***arr_not_envp, char **arr)
{
	int		j;
	int		i;
	char	**local_arr;
	char	*old_temp;

	i = 0;
	j = 0;
	*temp = "";
	*arr_not_envp = ft_split(node->value, ' ');
	if (!*arr_not_envp)
		return ;
	while ((*arr_not_envp)[j])
	{
		local_arr = ft_split(node->value, ' ');
		if (!local_arr)
			break ;
		while (local_arr[i])
		{
			if (ft_strchr(local_arr[i], '$') == NULL)
			{
				old_temp = *temp;
				*temp = ft_strjoin(*temp, " ");
				//free(old_temp);
				old_temp = *temp;
				*temp = ft_strjoin(*temp, local_arr[i]);
				free(old_temp);
			}
			i++;
		}
		free_array(local_arr, array_len(local_arr));
		j++;
	}
}

void	handle_not_found_env_var(t_ast_node *node, char **envp, char **arr)
{
	char	*temp;
	char	**arr_not_envp;
	char	**value_to_search;
	char	*valid_path;

	search_for_cmd_in_array(node, &temp, &arr_not_envp, arr);
	free_array(arr_not_envp, array_len(arr_not_envp));

	if (ft_strcmp(temp, "") == 0 || temp == NULL)
		return ;
	node->value = ft_strdup(temp);
	free(temp);
	value_to_search = ft_split(node->value, ' ');
	valid_path = search_valid_path(value_to_search[0], envp);
	if (!valid_path)
	{
		node->value = value_to_search[0];
		free_array(value_to_search, array_len(value_to_search));
		
		check_and_execute_if_is_cmd(node, envp);
		return ;
	}
	free(valid_path);
	free_array(value_to_search, array_len(value_to_search));
	check_if_is_cmd_or_dir(node, envp);
	return ;
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
