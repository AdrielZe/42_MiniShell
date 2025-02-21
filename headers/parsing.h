/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:38:26 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/29 16:03:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "main.h"

struct	s_tokens;

typedef struct s_delim
{
	char			*delimiter;
	struct s_delim	*next;
}	t_delim;

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
	int					outfile;
	t_node_type			outfile_type;
	int					infile;
	int					env_var;
}	t_ast_node;

t_ast_node	*create_node(t_node_type type, char *value);
t_ast_node	*build_ast(struct s_tokens *tokens);
int			search_for_path_index(char **envp);
void		parse_commands(t_ast_node *node, char **envp);
void		create_pipe_node(t_ast_node	**root, t_ast_node **current);
char		**split_with_quotes(const char *s);
void		create_command_node(t_ast_node **root,
				t_ast_node **current, struct s_tokens *tokens);
void		create_envp_node(t_ast_node **root,
				t_ast_node **current, struct s_tokens *tokens);
void		create_heredoc_node(t_ast_node	**root, t_ast_node **current);
void		handle_heredoc(t_ast_node *node, char **envp);
void		read_heredoc(int *pipefd, t_delim *delimiter);
void	handle_node_types(t_ast_node *node, char **envp, t_delim **delimiters);
void	handle_nodes_to_execute_command(t_ast_node *current, int pipe_found, t_ast_node *node, char **envp);
t_delim	*create_delim_list(char **delims);
t_delim *get_all_delimiters(t_ast_node *node);
void		check_all_commands(t_ast_node *node, char **envp);
char		*if_env_var(t_ast_node *node, char **tokens);
void		free_delimiters(t_delim *head);
void		skip_quotes(char *quote_char, const char **s);
void	count_word_len_split(const char **s, int *len);
void	find_string_end(const char **s, char *quote_char, int *in_quotes, const char **start);
int	is_space(char c);
int	get_word_length(const char **s, int *len, int *in_quotes, char *quote_char);
void		exit_if_invalid_path(char **cmd);
void		free_paths(char **paths);
char		*search_valid_path(char *cmd, char **envp);
void		free_cmd(char **cmd);
void		execute_command(char *argv, char **envp, t_ast_node *node);
int			open_stdin(char *file);
int			open_append(char *file);
int			open_stdout(char *file);
int			check_outfile(t_ast_node *node, int fd);

#endif