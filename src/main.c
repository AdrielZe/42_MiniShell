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

int	main(int argc, char *argv[], char *envp[])
{
	char		**token;
	t_tokens	*token_list;
	t_ast_node	*root;

	if (argc && argv)
		printf(" ");
	token_list = NULL;
	init_shell(&token, &token_list, envp, &root);
	clear_token_list(&token_list);
	write_history(".my_history");
	return (0);
}
