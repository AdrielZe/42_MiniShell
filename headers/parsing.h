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

//src/ast_tokens.c
void		create_heredoc_node(t_ast_node	**root, t_ast_node **current);
void		create_pipe_node(t_ast_node	**root, t_ast_node **current);
void		create_command_node(t_ast_node **root,
				t_ast_node **current, struct s_tokens *tokens);
void		create_envp_node(t_ast_node **root,
				t_ast_node **current, struct s_tokens *tokens);
void		create_word_node(t_ast_node **root,
				t_ast_node **current, struct s_tokens *tokens);

//src/build_ast.c
t_ast_node	*create_node(t_node_type type, char *value);
t_ast_node	*build_ast(struct s_tokens *tokens);

//src/command_execution_1.c
void		parse_commands(t_ast_node *node, char **envp);

//src/command_execution_2.c
void		handle_node_types(t_ast_node *node,
				char **envp, t_delim **delimiters);
int			is_directory(char *path);
int			is_file(const char *path);

//src/command_execution_3.c
void		handle_word_node(t_ast_node *node, char **envp);
void		when_only_env_var(t_ast_node *node, char **envp, char *old_string);
void		check_and_execute_if_is_cmd(t_ast_node *node, char **envp);
void		execute_regular_cmd(t_ast_node *node, char **envp);
void		free_split(char **split);
int			verify_if_is_env_var(t_ast_node *node);

//src/command_execution_4.c
void		handle_command_node(t_ast_node *node, char **envp);
void		check_if_is_cmd_or_dir(t_ast_node *node, char **envp);
void		check_if_is_directory(char *node_value);
void		handle_node_value(t_ast_node *node, char **envp, char *old_string);

//src/command_execution_5.c
int			found_env_var(t_ast_node *node, char *old_string);
void		execute_valid_cmd(t_ast_node *node, char **envp, char *cmd);
void		handle_found_env_var(t_ast_node *node, char **envp, char *cmd);

//src/command_execution_6.c
void		search_for_cmd_in_array(t_ast_node *node, char **temp,
				char ***arr_not_envp, char **arr);
void		handle_not_found_env_var(t_ast_node *node, char **evnp, char **arr);
int			is_only_spaces(char *str);

//src/search_path_1.c
char		*search_valid_path(char *cmd, char **envp);

//src/search_path_2.c
void		execute_command(char *argv, char **envp,
				t_ast_node *node);

//src/split_quotes_1.c
char		**split_with_quotes(char *s);
char		*extract_word(char **s);
int			is_space(char c);

//src/split_quotes_2.c
void		skip_quotes(char *quote_char, char **s);
int			get_word_length(char **s, int *len,
				int *in_quotes, char *quote_char);

//src/heredoc/heredoc_1.c
void		read_heredoc(int *pipefd, t_delim *delimiter);
void		handle_heredoc(t_ast_node *node, char **envp);

//src/heredoc/heredoc_2.c
t_delim		*get_all_delimiters(t_ast_node *node);
void		free_delimiters(t_delim *head);
void		check_all_commands(t_ast_node *node, char **envp);

//src/heredoc/heredoc_3.c
void		handle_nodes_to_execute_command(t_ast_node *current,
				int pipe_found, t_ast_node *node, char **envp);
void		close_heredoc_prompt(void);

//src/redirection/open_file.c
int			open_stdin(char *file);
int			open_stdout(char *file);
int			open_append(char *file);
int			check_outfile(t_ast_node *node, int fd);

//src/parsing/command_direction.c
void	execute_cmd_or_word(t_ast_node *node, char *command_to_execute, char **envp);
void	print_not_found_msg_and_free(char *command_to_execute, t_ast_node *node, char **split_values);
void	get_cmd_to_execute(t_ast_node *node, char ***split_values, char **command_to_execute);
void	free_resources(t_ast_node *node, char **split_values, char *search_result);
void	get_cmds_to_execute(char **old_temp, char **temp, char **local_arr, int i);

char	*if_env_var(t_ast_node *node, char **tokens);
void	execute_word_node(t_ast_node *node, char *cmd, char **envp);
void	execute_node_command(t_ast_node *node, char *cmd, char **envp);
void	setup_tokens_and_commands(t_ast_node *node, char ***tokens, char **cmd, char ***cmd_to_split);
void	open_pid(int *pid);
void	close_pipefd(int *pipefd);
void	write_and_free_input(int *pipefd, char *input);
int	node_exists(t_ast_node *node);

#endif