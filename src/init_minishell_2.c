/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:36:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/19 09:26:42 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	exit_if_typed_exit(char *input,
	t_tokens **token_list, char **envp_copy)
{
	if (ft_strcmp("exit", input) == 0)
	{
		clear_token_list(token_list);
		free_array(envp_copy);
		free(input);
		printf("Exiting.\n");
		exit(0);
	}
}

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
			printf("Syntax error: redirects\n");
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
			printf("Syntax error: pipes\n");
			write_exitcode(2);
			return (0);
		}
	}
	return (1);
}

int	check_syntax(t_tokens *tokens)
{
	t_tokens	*current;

	current = tokens;
	while (current)
	{
		if (redirects_verification(current) == 0)
			return (0);
		if (pipes_verification(current) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}
