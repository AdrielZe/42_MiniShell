/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:03:29 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/05 17:17:01 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	write_and_free_input(int *pipefd, char *input)
{
	write(pipefd[1], input, ft_strlen(input));
	write(pipefd[1], "\n", 1);
	free(input);
}

void	display_input_line(char **input)
{
	*input = readline("heredoc> ");
	if (!*input)
	{
		close_heredoc_prompt();
		return ;
	}
}
