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

#include "../headers/main.h"

int	ft_exit(const char **args, char **envp)
{
	char	**args_array;
	int		exit_code;

	exit_code = 127;
	args_array = ft_split(*args, ' ');
	remove_quotes(args_array[0]);
	if (array_len(args_array) > 1)
		remove_quotes(args_array[1]);
	if (ft_strcmp(args_array[0], "exit") != 0)
	{
		free_array(args_array);
		return (0);
	}
	if (!args_array)
		return (0);
	if (!args_array[0])
		return (0);
	if (array_len(args_array) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		add_exitcode(1);
		return (1);
	}
	if (array_len(args_array) > 1 && !ft_isnumeric(args_array[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args_array[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (1);
	}
	if (array_len(args_array) > 1 && ft_isnumeric(args_array[1]))
		exit_code = ft_atoi(args_array[1]) % 256;
	free_array(args_array);
	free_array(envp);
	exit(exit_code);
	return (0);
}

void	handle_word_quotes(char *new_word,
				int *is_executable, char **envp, int index)
{
	char	*unquoted_word;

	if (!new_word)
		return ;
	unquoted_word = ft_strdup(new_word);
	if (!unquoted_word)
		return ;
	remove_quotes(unquoted_word);
	if (search_valid_path(unquoted_word, envp) != NULL && index != 0)
		*is_executable = 1;
	free(unquoted_word);
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
			&& ft_strcmp((*data->array)[*(data->i) - 1], ">>") != 0)
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
