/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:38:26 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/23 20:27:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../headers/main.h"

typedef enum e_node_type
{
	NODE_WORD,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_ENV_VAR,
	NODE_COMMAND,
}	t_node_type;

typedef struct s_ast_node
{
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_node_type			type;
	char				*value;
}	t_ast_node;

t_ast_node	*create_node(t_node_type type, char *value);
t_ast_node	*build_ast(t_tokens *tokens);
char		*parse_commands(t_ast_node *node, char **envp);
void		create_pipe_node(t_ast_node	**root, t_ast_node **current);
void		create_command_node(t_ast_node **root,
				t_ast_node **current, t_tokens *tokens);
void		exit_if_invalid_path(char **cmd);
void		free_paths(char **paths);
char		*search_valid_path(char *cmd, char **envp);
int		search_for_path_index(char **envp);
void		free_cmd(char **cmd);
void		execute_command(char *argv, char **envp);


#endif