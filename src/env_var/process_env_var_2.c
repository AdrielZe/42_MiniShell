/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_var_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:16:06 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/19 09:21:08 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

char	*replace_substring(char *string, char *replace_string, int index)
{
	char	*string_rest;
	char	*env_value;
	char	*new_string;
	int		new_length;

	string_rest = ft_substr(string, index + ft_strlen(replace_string) + 1,
			ft_strlen(string) - index);
	if (!string_rest)
		return (string);
	if (ft_strcmp(replace_string, "?") == 0)
		env_value = getenv("EXITCODEMINISHELL");
	else
		env_value = getenv(replace_string);
	if (!env_value)
		env_value = "";
	new_length = index + ft_strlen(env_value) + ft_strlen(string_rest) + 1;
	new_string = malloc(new_length);
	if (!new_string)
		return (string);
	ft_strlcpy(new_string, string, index + 1);
	ft_strlcat(new_string, env_value, new_length);
	ft_strlcat(new_string, string_rest, new_length);
	free(string_rest);
	return (new_string);
}
