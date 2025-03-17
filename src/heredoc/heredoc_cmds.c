/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:09:05 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/17 11:10:57 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

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

static char	*extract_next_quoted(const char **s, char quote)
{
	const char	*start;
	char		*str;

	start = ++(*s);
	while (**s && **s != quote)
		(*s)++;
	if (**s == quote)
	{
		str = ft_strndup(start, *s - start);
		(*s)++;
		return (str);
	}
	return (NULL);
}

char	**extract_quoted_strings(const char *s)
{
	char	**quoted_strings;
	int		i;

	i = 0;
	quoted_strings = malloc(sizeof(char *) * 100);
	if (!quoted_strings)
		return (NULL);
	while (*s)
	{
		if (*s == '\'')
		{
			quoted_strings[i] = extract_next_quoted(&s, *s);
			if (quoted_strings[i])
				i++;
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

void	exec_heredoc_cmds(t_ast_node *node, t_ast_node *current, char **envp)
{
	char	*value;
	char	**new_args;

	value = search_valid_path(ft_split(current->value, ' ')[0], envp);
	new_args = prepare_exec_args(node, current, envp);
	if (execve(value, new_args, envp) == -1)
	{
		perror("execve\n");
		exit(2);
	}
	free_array(new_args);
}
