/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmds_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:09:05 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/17 11:13:33 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

t_heredoc_data	*get_heredoc_data(void)
{
	static t_heredoc_data	data = {NULL, NULL};

	return (&data);
}

char	*get_quoted_string(const char **s, char quote)
{
	const char	*start;

	start = *s;
	while (**s && **s != quote)
		(*s)++;
	if (**s == quote)
	{
		(*s)++;
		return (strndup(start, *s - start - 1));
	}
	return (NULL);
}

void	remove_array_quotes(char ***array)
{
	int	i;

	i = 0;
	while ((*array)[i])
	{
		remove_quotes((*array)[i]);
		i++;
	}
}

char	**place_simple_quote(char **array, char **in_quote)
{
	char		**new_array;
	int			i;
	int			j;

	new_array = malloc((array_len(array) + 1) * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		j = 0;
		new_array[i] = ft_strdup(array[i]);
		while (in_quote[j])
		{
			if (ft_strcmp(array[i], in_quote[j]) == 0)
			{
				free(new_array[i]);
				new_array[i] = add_quote_type_str(in_quote[j], '\'');
				break ;
			}
			j++;
		}
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

char	**prepare_exec_args(t_ast_node *node, t_ast_node *current, char **envp)
{
	char	**args;
	char	**value_splitted;
	char	*value;
	char	**in_quote;
	char	**new_args;

	args = split_with_quotes(node->right->value);
	value_splitted = ft_split(current->value, ' ');
	args = replace_at_index(args, array_len(args), 0, value_splitted[0]);
	value = search_valid_path(value_splitted[0], envp);
	in_quote = extract_quoted_strings(node->right->value);
	new_args = place_simple_quote(args, in_quote);
	free_array(args);
	new_args = map_strings(new_args, array_len(new_args), process_env_var);
	free_array(value_splitted);
	remove_array_quotes(&new_args);
	return (new_args);
}
