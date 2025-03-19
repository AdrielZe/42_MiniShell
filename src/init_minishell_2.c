/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:36:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/19 19:08:03 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	free_token(char ***token)
{
	int	i;

	if (!*token)
		return ;
	i = 0;
	while ((*token)[i])
	{
		free((*token)[i]);
		i++;
	}
	free(*token);
	*token = NULL;
}

int	redirects_verification(t_tokens *current)
{
	if (current->type == TOKEN_APPEND || current->type == TOKEN_HEREDOC
		|| current->type == TOKEN_REDIRECT_IN
		|| current->type == TOKEN_REDIRECT_OUT)
	{
		if (!current->next || (current->next->type != TOKEN_WORD
				&& current->next->type != TOKEN_COMMAND
				&& current->next->type != TOKEN_SIMPLE_QUOTE))
		{
			printf("syntax error: redirects\n");
			write_exitcode(2);
			return (0);
		}
	}
	return (1);
}

int	pipes_verification(t_tokens *current)
{
	if (current->type == TOKEN_PIPE)
	{
		if (!current->next || (current->next
				&& current->next->type == TOKEN_PIPE))
		{
			printf("syntax error: pipes\n");
			write_exitcode(2);
			return (0);
		}
	}
	return (1);
}

int	slash_verification(t_tokens *current, char **envp)
{
	char	*cmd_value;
	char	**split_path;
	char	*valid_path;

	cmd_value = ft_strdup(current->value);
	split_path = split_with_quotes(cmd_value);
	if (!split_path)
		return (0);
	valid_path = search_valid_path(split_path[0], envp);
	if (split_path[0][0] == '/')
	{
		if (!valid_path)
		{
			free_array(split_path);
			free(cmd_value);
			return (0);
		}
	}
	free(cmd_value);
	free(valid_path);
	free_array(split_path);
	return (1);
}

int	check_syntax(t_tokens *tokens, char **envp)
{
	t_tokens	*current;

	current = tokens;
	while (current)
	{
		if (redirects_verification(current) == 0)
			return (0);
		if (pipes_verification(current) == 0)
			return (0);
		if (slash_verification(current, envp) == 0)
		{
			printf("minishell: no such file or directory: %s \n",
				current->value);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
