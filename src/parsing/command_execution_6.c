/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:17:45 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/26 21:58:48 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	search_for_cmd_in_array(t_ast_node *node,
				char **temp, char ***arr_not_envp, char **arr)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	*temp = "";
	*arr_not_envp = ft_split(node->value, ' ');
	while (arr_not_envp[j])
	{
		arr = ft_split(node->value, ' ');
		while (arr[i])
		{
			if (ft_strchr(arr[i], '$') == NULL)
			{
				*temp = ft_strjoin(*temp, " ");
				*temp = ft_strjoin(*temp, arr[i]);
			}
			i++;
		}
		j++;
	}
}

void	handle_not_found_env_var(t_ast_node *node, char **envp, char **arr)
{
	char	*temp;
	char	**arr_not_envp;

	search_for_cmd_in_array(node, &temp, &arr_not_envp, arr);
	if (ft_strcmp(temp, "") == 0 || temp == NULL)
		return ;
	node->value = ft_strdup(temp);
	if (!search_valid_path(ft_split(node->value, ' ')[0], envp))
	{
		node->value = ft_split(node->value, ' ')[0];
		check_and_execute_if_is_cmd(node, envp);
		return ;
	}
	check_if_is_cmd_or_dir(node, envp);
	return ;
}
