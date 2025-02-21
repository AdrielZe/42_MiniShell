/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/21 18:31:06 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <sys/stat.h>

int is_directory(char *path)
{
	struct stat path_stat;
	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

void handle_node_types(t_ast_node *node, char **envp, t_delim **delimiters)
{
    if (node->type == NODE_HEREDOC)
    {
        *delimiters = get_all_delimiters(node);
        handle_heredoc(node, envp);
    }
    else if (node->type == NODE_COMMAND)
    {
        char old_char = node->value[0];
        node->value = process_env_var(node->value);

        if (old_char == '$')
        {
            // Verifica se o valor é um diretório
            if (is_directory(node->value))
            {
                fprintf(stderr, "minishell: %s: Is a directory\n", node->value);
                return;
            }

            // Tenta executar o valor como um comando
            execute_command(node->value, envp, node, 1);
        }
        else if (ft_strchr(node->value, '/') != NULL)
        {
            if (ft_split(node->value, ' ')[0])
            {
                if (search_valid_path(ft_split(node->value, ' ')[0], envp) == NULL)
                {
                    printf("minishell: %s: command not found\n", ft_split(node->value, ' ')[0]);
                    return;
                }
            }
            execute_command(node->value, envp, node, 0);
        }
        else
        {
            execute_command(node->value, envp, node, 0);
        }
    }
}
	// else if (node->type == NODE_ENV_VAR)
	// {
	// 	node->value = process_env_var(node->value);
	// 	if (access(node->value, F_OK) == 0) // Se o caminho existe
	// 	{
    	// 		if (access(node->value, X_OK) == -1) // Se não for executável
    	// 		{
       //  			if (is_directory(node->value)) // Se for um diretório
       //      				fprintf(stderr, "minishell: %s: Is a directory\n", node->value);
       //  			else
       //      				fprintf(stderr, "minishell: %s: Permission denied\n", node->value);
       // 			return;
    	// 		}
	// 	}
	// 	else if (node->value[0] == '/') // Se não existe e começa com '/'
	// 	{
    	// 		fprintf(stderr, "minishell: %s: No such file or directory\n", node->value);
    	// 		return;
	// 	}  else
	// 		execute_command(node->value, envp, node, 1);
	// }

