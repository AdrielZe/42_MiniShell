/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:09:05 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/16 21:13:35 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

t_heredoc_data	*get_heredoc_data(void)
{
	static t_heredoc_data	data = {NULL, NULL};

	return (&data);
}

void	find_command_node(t_ast_node *node,
		t_ast_node **current, int pipe_found, char **envp)
{
	*current = (*current)->left;
	if ((*current)->type == NODE_PIPE && pipe_found == 0)
	{
		pipe_found = 1;
		if (node->right->outfile)
			dup2(node->right->outfile, STDOUT_FILENO);
		execute_command((*current)->right->value, envp, node);
	}
}	

char	**extract_quoted_strings(const char *s)
{
	char		**quoted_strings;
	const char	*start;
	char		quote;
	int			count;
	int			i;

	count = 0;
	i = 0;
	quoted_strings = malloc(sizeof(char *) * 100);
	if (!quoted_strings)
		return (NULL);
	while (*s)
	{
		if (*s == '\'')
		{
			quote = *s++;
			start = s;
			while (*s && *s != quote)
				s++;
			if (*s == quote)
			{
				quoted_strings[i] = strndup(start, s - start);
				i++;
				s++;
			}
		}
		else
			s++;
	}
	quoted_strings[i] = NULL;
	return (quoted_strings);
}

char	*add_quote_type_str(const char *s, char quote)
{
	char	*quoted_str;
	int		len;

	if (!s)
		return (NULL);
	if (s[0] == quote && s[ft_strlen(s) - 1] == quote)
		return (ft_strdup(s));
	len = ft_strlen(s) + 2;
	quoted_str = malloc(len + 1);
	if (!quoted_str)
		return (NULL);
	quoted_str[0] = quote;
	ft_strcpy(quoted_str + 1, s);
	quoted_str[len - 1] = quote;
	quoted_str[len] = '\0';
	return (quoted_str);
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
				printf("in quote: %s\n", new_array[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

void	exec_heredoc_cmds(t_ast_node *node, t_ast_node *current, char **envp)
{
	char	*string;
	char	**args;
	char	**value_splitted;
	char	*value;
	char	**in_quote;
	char	**new_args;

	string = node->right->value;
	in_quote = extract_quoted_strings(string);
	args = split_with_quotes(string);
	value_splitted = ft_split(current->value, ' ');
	value = search_valid_path(value_splitted[0], envp);
	args = replace_at_index(args, array_len(args), 0, value_splitted[0]);
	new_args = place_simple_quote(args, in_quote);
	free_array(args);
	new_args = map_strings(new_args, array_len(new_args), process_env_var);
	free_array(value_splitted);
	if (execve(value, new_args, envp) == -1)
	{
		perror("execve\n");
		exit(2);
	}
	free_array(new_args);
}
