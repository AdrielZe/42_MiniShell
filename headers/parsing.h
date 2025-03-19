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

typedef struct s_heredoc_data
{
	int		*pipefd;
	t_delim	*delimiters;
}	t_heredoc_data;

typedef enum e_node_type
{
	NODE_WORD,
	NODE_SIMPLE_QUOTE,
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
	int					lastcmd;
}	t_ast_node;

//src/build_ast.c
t_ast_node	*build_ast(struct s_tokens *tokens);
t_ast_node	*create_node(t_node_type type, char *value);

void		clean_exit(int exit_code, char **envp,
				struct s_tokens **token_list, t_ast_node *node);
int			handle_exit_errors(char **args_array);
char		*replace_substring(char *string, char *replace_string, int index);
void		protect_fork(pid_t *pid);
void		open_heredoc_pipe(int *pipefd, pid_t *pid);
void		get_cmd(t_ast_node *node, char **cmd, char ***tokens);
int			control_path(char **path, char *cmd, char **envp, char **tokens);
void		cleanup_heredoc(struct s_ast_node *node, char **envp);
void		free_array(char **array);
int			is_word_in_array(char *word, char **array);
void		remove_array_quotes(char ***array);
char		**place_simple_quote(char **array, char **in_quote);
char		*add_quote_type_str(const char *s, char quote);
char		**prepare_exec_args(t_ast_node *node, t_ast_node *current,
				char **envp);
char		**extract_quoted_strings(const char *s);
int			is_only_dollar(const char *str);
int			control_syntax(char *s_copy, char **array);
int			check_pipe_syntax(const char *s);
int			is_only_slash(const char *str);
//src/ast_tokens.c
void		create_heredoc_node(t_ast_node	**root, t_ast_node **current);
void		create_pipe_node(t_ast_node	**root, t_ast_node **current);
void		create_command_node(t_ast_node **root,
				t_ast_node **current, struct s_tokens *tokens);
void		create_envp_node(t_ast_node **root,
				t_ast_node **current, struct s_tokens *tokens);
void		create_word_node(t_ast_node **root,
				t_ast_node **current, struct s_tokens *tokens);

//src/command_execution_1.c
void		parse_commands(t_ast_node *node, char **envp);

//src/command_execution_2.c
void		handle_node_types(t_ast_node *node,
				char **envp, t_delim **delimiters);
int			is_directory(char *path);
int			is_file(const char *path);

//src/command_execution_3.c
void		handle_word_node(t_ast_node *node, char **envp);
void		when_only_env_var(t_ast_node *node, char **envp);
void		check_and_execute_if_is_cmd(t_ast_node *node, char **envp);
void		execute_regular_cmd(t_ast_node *node, char **envp);
void		free_split(char **split);
int			verify_if_is_env_var(t_ast_node *node);

//src/command_execution_4.c
void		handle_command_node(t_ast_node *node, char **envp);
void		check_if_is_cmd_or_dir(t_ast_node *node, char **envp);
void		handle_node_value(t_ast_node *node, char **envp, char *old_string);
int			check_if_is_directory(char *node_value);

//src/command_execution_5.c
int			found_env_var(t_ast_node *node, char *old_string);
void		execute_valid_cmd(t_ast_node *node, char **envp, char *cmd);
void		handle_found_env_var(t_ast_node *node, char **envp, char *cmd);

//src/command_execution_6.c
void		search_for_cmd_in_array(t_ast_node *node, char **temp,
				char ***arr_not_envp);
void		handle_not_found_env_var(t_ast_node *node, char **evnp);
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
void		read_heredoc(int *pipefd, t_delim *delimiters,
				t_ast_node *node, char **envp);
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
void		execute_cmd_or_word(t_ast_node *node,
				char *command_to_execute, char **envp);
void		print_not_found_msg_and_free(char *command_to_execute,
				t_ast_node *node, char **split_values);
void		get_cmd_to_execute(t_ast_node *node,
				char ***split_values, char **command_to_execute);
void		free_resources(t_ast_node *node,
				char **split_values);
void		get_cmds_to_execute(char **old_temp,
				char **temp, char **local_arr, int i);

void		execute_word_node(t_ast_node *node, char *cmd, char **envp);
void		execute_node_command(t_ast_node *node, char *cmd, char **envp);
void		setup_tokens_and_commands(t_ast_node *node,
				char ***tokens, char **cmd, char ***cmd_to_split);
void		close_pipefd(int *pipefd);
void		open_pid(int *pid);
void		write_and_free_input(int *pipefd, char *input);
char		*if_env_var(t_ast_node *node, char **tokens);
int			node_exists(t_ast_node *node);

void		create_simple_quote_node(t_ast_node **root,
				t_ast_node **current, struct s_tokens *tokens);
void		cleanup_heredoc_c(t_ast_node *node, char **envp);
void		handle_cmd_or_word_token(struct s_tokens *tokens,
				t_ast_node **root, t_ast_node **current);
int			redirection_if(struct s_tokens *tokens, t_ast_node *node);
void		handle_ctrl_d_heredoc(char **envp_copy,
				struct s_tokens **token_list, t_ast_node *root);
void		not_found_msg_and_free(t_ast_node *node, char *search_result,
				char **split_values, char *command_to_execute);
void		create_nodes_and_redirect_if(struct s_tokens **tokens,
				t_ast_node **root, t_ast_node **current);
void		handle_env_var(t_ast_node *node, char **envp, char *old_string);
int			if_cd(char *cmd, char **envp);
void		process_command_execution(t_ast_node *node,
				char **envp, char *old_string, char **split_result);
void		execute_command_for_node_function(char *path,
				char **tokens, char **envp);
char		*resolve_path(char *cmd, char **envp);
void		display_input_line(char **input, char **envp, t_ast_node *node);
void		handle_simple_quote_node(t_ast_node *node, char **envp);
void		free_env_and_array(char *env_result, char **env_processed);
void		update_node_value(t_ast_node *node, char *new_value);
void		process_local_array(char **temp, char **arr_not_envp);
void		process_valid_path(t_ast_node *node,
				char **value_to_search, char **envp);
void		execute_simple_quote_node(t_ast_node *node, char *cmd, char **envp);
void		valid_outfile_and_path(char *cmd, char *path);
void		remove_quotes(char *str);
void		get_new_word(char **new_word, const char **s, char ***array);
int			execute_command_for_word_node(char *path,
				char **tokens, char **envp);
int			control_command_execution_with_slash(char ***split_path,
				t_ast_node *node, char **envp);
void		rmv_quotes_set_cmd(t_ast_node *node,
				char ***split_values, char **command_to_execute);
int			not_result_msg_free(char *search_result, t_ast_node *node,
				char **split_values, char *command_to_execute);
void		open_left_pipe(int *pipefd, pid_t *pid_left);
void		open_right_pipe(pid_t *pid_right);
void		right_process(int *pipe, t_ast_node *node, char **envp);
void		left_process(int *pipe, t_ast_node *node,
				t_delim *delimiters, char **envp);
char		**replace_at_index(char **array, int size,
				int index, const char *new_value);
char		**map_strings(char **array, int size, char *(*func)(char *, int));
void		exec_heredoc_cmds(t_ast_node *node,
				t_ast_node *current, char **envp);
void		find_command_node(t_ast_node *node,
				t_ast_node **current, int pipe_found, char **envp);
int			consumes_stdin(char *command, char **envp);
void		handle_execution_failure(char *cmd, char **tokens);
void		execute_child_process(char *cmd,
				char *path, char **tokens, char **envp);
void		if_not_path(char *cmd, char **tokens);
int			is_src_file(char *cmd);
void		wait_for_processes(pid_t pid_left, pid_t pid_right, int *status);
int			should_wait_left_process(t_ast_node *node,
				pid_t pid_left, int *status);
void		handle_right_process(pid_t pid_right,
				int *pipefd, t_ast_node *node, char **envp);
char		*get_quoted_string(const char **s, char quote);

#endif