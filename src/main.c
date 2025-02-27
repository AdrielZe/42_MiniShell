/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:56:21 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/29 16:04:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include "../headers/tokenize.h"
#include "../headers/parsing.h"
#include <signal.h>

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

static char	**copy_envp(char *envp[])
{
	int		i;
	char	**envp_copy;

	i = 0;
	while (envp[i])
		i++;
	envp_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_copy)
	{
		perror("malloc");
		exit(1);
	}
	i = 0;
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		**token;
	t_tokens	*token_list;
	char		**envp_copy;
	int			len;
	t_ast_node	*root;

	(void) argc;
	(void) argv;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	envp_copy = copy_envp(envp);
	token_list = NULL;
	init_shell(&token, &token_list, envp_copy, &root);
	clear_token_list(&token_list);
	write_history(".my_history");
	len = array_len(envp_copy);
	free_array(envp_copy, len);
	return (0);
}
