/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:22:50 by marvin            #+#    #+#             */
/*   Updated: 2025/03/08 21:22:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	process_exit_code(char **args_array)
{
	if (array_len(args_array) > 1 && ft_isnumeric(args_array[1]))
		return (ft_atoi(args_array[1]) % 256);
	return (127);
}

int	validate_exit_args(char **args_array)
{
	if (!args_array || !args_array[0])
		return (0);
	remove_quotes(args_array[0]);
	if (array_len(args_array) > 1)
		remove_quotes(args_array[1]);
	if (ft_strcmp(args_array[0], "exit") != 0)
		return (0);
	return (handle_exit_errors(args_array));
}

int	ft_exit(char *args, char **envp, t_tokens **token_list, t_ast_node *node)
{
	char	**args_array;
	int		exit_code;

	if (!args)
		return (0);
	args_array = split_with_quotes(args);
	if (validate_exit_args(args_array) == 0)
	{
		free_array(args_array);
		return (0);
	}
	exit_code = process_exit_code(args_array);
	free_array(args_array);
	clean_exit(exit_code, envp, token_list, node);
	return (0);
}

void	handle_word_quotes(char *new_word,
				int *is_executable, char **envp, int index)
{
	char	*unquoted_word;
	char	*valid_path;

	if (!new_word)
		return ;
	unquoted_word = ft_strdup(new_word);
	if (!unquoted_word)
		return ;
	remove_quotes(unquoted_word);
	valid_path = search_valid_path(unquoted_word, envp);
	free(unquoted_word);
	if (!valid_path)
		return ;
	if (valid_path != NULL && index != 0)
		*is_executable = 1;
	free(valid_path);
}

void	process_new_word(char *new_word, t_word_data *data)
{
	if (*(data->i) == 0 || ft_strcmp(new_word, "|") == 0
		|| ft_strcmp(new_word, "<") == 0
		|| ft_strcmp(new_word, ">") == 0
		|| ft_strcmp(new_word, "<<") == 0)
	{
		alloc_new_word_in_array(data->array,
			data->i, new_word);
		*(data->is_executable) = 0;
	}
	else if (ft_strcmp((*data->array)[*(data->i) - 1], "|") != 0
			&& ft_strcmp((*data->array)[*(data->i) - 1], "<") != 0
			&& ft_strcmp((*data->array)[*(data->i) - 1], ">") != 0
			&& ft_strcmp((*data->array)[*(data->i) - 1], "<<") != 0
			&& ft_strcmp((*data->array)[(*data->i) - 1], ">>") != 0)
	{
		merge_last_token(data->array, *(data->i), new_word);
		*(data->is_executable) = 0;
		data->old_string = NULL;
	}
	else
	{
		alloc_new_word_in_array(data->array, data->i,
			new_word);
	}
}
