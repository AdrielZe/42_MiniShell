/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:09:05 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/16 06:57:15 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

t_heredoc_data	*get_heredoc_data(void)
{
	static t_heredoc_data	data = {NULL, NULL};

	return (&data);
}

void	find_command_node(t_ast_node *node,
		t_ast_node **current, int pipe_found, char **envp)
{
	*current = (*current)->left;
	if ((*current)->type == NODE_PIPE && pipe_found == 0)
	{
		pipe_found = 1;
		if (node->right->outfile)
			dup2(node->right->outfile, STDOUT_FILENO);
		execute_command((*current)->right->value, envp, node);
	}
}	

char	**extract_quoted_strings(const char *s)
{
	char	**quoted_strings;
	int		count;
	int		i;
	const char	*start;
	char		quote;

	count = 0;
	i = 0;
	quoted_strings = malloc(sizeof(char *) * 100);
	if (!quoted_strings)
		return (NULL);
	while (*s)
	{
		if (*s == '\'')
		{
			quote = *s++;
			start = s;
			while (*s && *s != quote)
				s++;
			if (*s == quote)
			{
				quoted_strings[i] = strndup(start, s - start);
				i++;
				s++; // Pular a aspa final
			}
		}
		else
			s++;
	}
	quoted_strings[i] = NULL; // Finaliza o array com NULL
	return (quoted_strings);
}
char *add_quote_type_str(const char *s, char quote) {
	int len;
	char *quoted_str;
   
	if (!s)
	    return NULL;
   
	// Verifica se a string já está entre aspas
	if (s[0] == quote && s[ft_strlen(s) - 1] == quote) {
	    return ft_strdup(s); // Já está entre aspas, retorna uma cópia
	}
   
	len = ft_strlen(s) + 2; // +2 para as aspas
	quoted_str = malloc(len + 1); // +1 para o '\0'
	if (!quoted_str)
	    return NULL;
   
	quoted_str[0] = quote;
	ft_strcpy(quoted_str + 1, s);
	quoted_str[len - 1] = quote;
	quoted_str[len] = '\0';
   
	return quoted_str;
   }
   
char **place_simple_quote(char **array, char **in_quote) {
	int i;
	int j;
	char **new_array;
   
	// Aloca memória para o novo array (mesmo tamanho do array original)
	new_array = malloc((array_len(array) + 1) * sizeof(char *));
	if (!new_array)
	    return NULL;
   
	i = 0;
	while (array[i]) {
	    j = 0;
	    new_array[i] = ft_strdup(array[i]); // Copia a string original
   
	    // Verifica se a string está na lista de strings entre aspas
	    while (in_quote[j]) {
		 if (ft_strcmp(array[i], in_quote[j]) == 0) {
		     // Libera a cópia anterior e adiciona aspas simples
		     free(new_array[i]);
		     new_array[i] = add_quote_type_str(in_quote[j], '\'');
		     printf("in quote: %s\n", new_array[i]);
		     break;
		 }
		 j++;
	    }
	    i++;
	}
   
	new_array[i] = NULL; // Finaliza o novo array com NULL
	return new_array;
   }
   void exec_heredoc_cmds(t_ast_node *node, t_ast_node *current, char **envp) {
	char *string;
	char **args;
	char **value_splitted;
	char *value;
	char **in_quote;
	char **new_args; // Novo array para armazenar as strings com aspas
   
	string = node->right->value;
	in_quote = extract_quoted_strings(string); // Extrai strings entre aspas
	args = split_with_quotes(string); // Divide a string em argumentos
   
	// Divide o valor do nó atual (comando) para buscar o caminho válido
	value_splitted = ft_split(current->value, ' ');
	value = search_valid_path(value_splitted[0], envp); // Busca o caminho do executável
   
	// Substitui o primeiro argumento pelo nome do executável
	args = replace_at_index(args, array_len(args), 0, value_splitted[0]);
   
	// Aplica aspas simples às strings necessárias e cria um novo array
	new_args = place_simple_quote(args, in_quote);
   
	// Libera o array antigo (args) após criar o novo array (new_args)
	free_array(args);
   
	// Debug: Imprime os argumentos
	int i = 0;
	while (new_args[i]) {
	    printf("args : %s\n", new_args[i]);
	    i++;
	}
   
	// Processa variáveis de ambiente nos argumentos
	new_args = map_strings(new_args, array_len(new_args), process_env_var);
   
	// Libera a memória alocada para value_splitted
	free_array(value_splitted);
   
	// Executa o comando
	if (execve(value, new_args, envp) == -1) {
	    perror("execve\n");
	    exit(2);
	}
   
	// Libera a memória do novo array (new_args) após o execve (não será alcançado se execve for bem-sucedido)
	free_array(new_args);
   }
