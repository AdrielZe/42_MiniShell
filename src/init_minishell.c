/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:36:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/28 17:40:09 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	exit_if_typed_exit(char *input,
			t_tokens **token_list, char **envp_copy)
{
	if (ft_strcmp("exit", input) == 0)
	{
		clear_token_list(token_list);
		free_array(envp_copy, array_len(envp_copy));
		free(input);
		printf("Saindo do programa.\n");
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
void	check_syntax(t_tokens *tokens, char **envp)
{
	t_tokens	*current;
	t_tokens	*temp;

	current = tokens->next;
	if(tokens->type != TOKEN_COMMAND && tokens->type != TOKEN_WORD)
	{
		printf("erro de syntax\n");
		clear_token_list(&tokens);
		free_array(envp, array_len(envp));
		exit(3);
	}
	while (current)
	{
		if(current->type == TOKEN_APPEND ||
			current->type == TOKEN_HEREDOC ||
			current->type == TOKEN_REDIRECT_IN ||
			current->type == TOKEN_REDIRECT_OUT)
			if (!current->next || current->next->type != TOKEN_WORD &&
				current->next->type != TOKEN_COMMAND)
            {
                printf("Erro de sintaxe: operador de redirecionamento sem arquivo.\n");
                clear_token_list(&tokens);
                free_array(envp, array_len(envp));
                exit(3);
            }
		if(current->type == TOKEN_PIPE)
		{
			if(!current->next || current->next->type == TOKEN_PIPE)
			{
				printf("Erro de sintaxe: pipes.\n");
                clear_token_list(&tokens);
                free_array(envp, array_len(envp));
                exit(3);
			}
		}
		current = current->next;
	}
	
}
void	init_shell(char ***token, t_tokens **token_list, char
			**envp, t_ast_node **root)
{
	char	*input;

	*token = NULL;
	while (1)
	{
		manage_rl_input(&input, envp, token_list, *root);
		if (!input || ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		setup_tokens_and_build_ast(input, token_list, envp, token);
		check_syntax(*token_list, envp);
		*root = build_ast(*token_list);
		print_list(*token_list);
		clear_token_list(token_list);
		parse_commands(*root, envp);
		if (*root)
		{
			free_ast(*root);
			*root = NULL;
		}
		if (input)
			add_history(input);
		free(input);
		input = NULL;
	}
}
