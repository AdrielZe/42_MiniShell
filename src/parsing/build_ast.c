/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:32:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/29 16:00:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

// Essa função não será usada qnd o projeto ficar pronto, apenas para testes, por isso ela está fora da norma
void print_ast(t_ast_node *node, int level)
{
    if (!node)
        return;

    // Indentação para visualizar a hierarquia
    for (int i = 0; i < level; i++)
        printf("  ");
    
    // Exibir o tipo e valor do nó
    printf("[%s: %s]\n", node->type == NODE_PIPE ? "PIPE" : "COMMAND", node->value);

    // Recursão para o filho esquerdo, se houver
    if (node->left)
    {
        for (int i = 0; i < level + 1; i++)  // Mais um nível de indentação para o filho esquerdo
            printf("  ");
        printf("[LEFT]\n");
        print_ast(node->left, level + 1);
    }

    // Recursão para o filho direito, se houver
    if (node->right)
    {
        for (int i = 0; i < level + 1; i++)  // Mais um nível de indentação para o filho direito
            printf("  ");
        printf("[RIGHT]\n");
        print_ast(node->right, level + 1);
    }
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->value)
		free(node->value);
	free(node);
}

t_ast_node	*create_node(t_node_type type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*build_ast(t_tokens *tokens)
{
	t_ast_node	*root;
	t_ast_node	*current;

	current = NULL;
	root = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			create_pipe_node(&root, &current);
		else if (tokens->type == TOKEN_COMMAND)
			create_command_node(&root, &current, tokens);
		tokens = tokens->next;
	}
	// print_ast(root, 0);
	return (root);
}

void parse_commands(t_ast_node *node, char **envp)
{
    int	pipefd[2];
    if (!node)
        return;

    if (node->type == NODE_PIPE)
	{
        if (pipe(pipefd) == -1)
		{
            perror("pipe");
            return;
        }
        pid_t pid_left = fork();
        if (pid_left < 0)
		{
            perror("fork left");
            return;
        }
        if (pid_left == 0) {
            if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			{
                perror("dup2 left");
                exit(1);
            }
            close(pipefd[0]);
            close(pipefd[1]);
            parse_commands(node->left, envp);
            exit(0);
        }
        pid_t pid_right = fork();
        if (pid_right < 0)
		{
            perror("fork right");
            return;
        }
        if (pid_right == 0)
		{
            if (dup2(pipefd[0], STDIN_FILENO) == -1)
			{
                perror("dup2 right");
                exit(1);
            }
            close(pipefd[0]);
            close(pipefd[1]);
            parse_commands(node->right, envp);
            exit(0);
        }
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid_left, NULL, 0);
        waitpid(pid_right, NULL, 0);
    }
    else if (node->type == NODE_COMMAND)
	{
        execute_command(node->value, envp);
    }
}

// char	*parse_commands(t_ast_node *node, char **envp)
// {
// 	char	*result;
// 	// char	*left_result;
// 	// char	*right_result;

// 	// left_result = NULL;
// 	// right_result = NULL;
// 	if (!node)
// 		return (NULL);
// 	result = malloc(1);
// 	if (node->type == NODE_PIPE)
// 	{
// 		// execute_command(node, envp, node);
// 		parse_commands(node->left, envp);
// 	}
// 	if (node->type == NODE_COMMAND)
// 	{
// 		execute_command(node->value, envp, node);
// 	}
// 	// if (node->left)
// 	// {
// 	// 	left_result = parse_commands(node->left, envp);
// 	// 	free(left_result);
// 	// }
// 	if (node->right)
// 	{
// 		right_result = parse_commands(node->right, envp);
// 		free(right_result);
// 	}
// 	return (result);
// }
