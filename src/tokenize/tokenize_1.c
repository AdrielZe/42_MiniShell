/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:59:58 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/29 16:03:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include "../../headers/parsing.h"

void	free_array(char **array)
{
    int i2 = 0;
    if (!array || !*array)
        return;
    while (array[i2])
    {
        free(array[i2]);
        i2++;
    }
    free(array);
}

char	*allocate_word(const char *s, int len)
{
	char	*word;

	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, s, len);
	word[len] = '\0';
	return (word);
}

size_t	ft_count_word(const char *s)
{
	size_t	count;
	size_t	delim_counter;

	delim_counter = 0;
	count = 0;
	while (*s)
	{
		s += count_if(&count, s);
		while (*s == '|')
		{
			delim_counter++;
			s++;
			if (*s)
				s++;
		}
		count++;
	}
	return (count + delim_counter);
}
int is_quoted(const char *s)
{
	int len;
	char	**cmd_split;

	len = 0;
	if (!s)
	{
		printf("Error: s is NULL\n");
		return 0;
	}
	if (s[0] == '"' || s[0] == '\'')
		return s[0];
	return (0);
}

void add_quote_type(char *s, char quote)
{
    int len;
    char *quoted_str;

    if (!s) // Verifica se a string é nula
        return;

    len = ft_strlen(s) + 2; // Calcula o novo comprimento da string (adicionando espaço para as aspas)

    // Aloca memória para a nova string com as aspas
    quoted_str = malloc(len + 1);  // +1 para o caractere nulo '\0'
    if (!quoted_str)
    {
        // Se a alocação falhar, retorna
        return;
    }

    // Coloca o tipo de aspa (quote) no início da string
    quoted_str[0] = quote;

    // Copia a string original para a nova string, começando da posição 1
    ft_strcpy(quoted_str + 1, s);

    // Coloca a mesma aspa no final da string
    quoted_str[len - 1] = quote;

    // Adiciona o caractere nulo no final
    quoted_str[len] = '\0';

    // Agora a string `quoted_str` contém a string original com as aspas ao redor
    // Em vez de retornar, você pode fazer o que for necessário com `quoted_str`
    // Exemplo: você pode copiar a string de volta para `s`, ou retornar, conforme a necessidade.
    ft_strcpy(s, quoted_str); // Se você deseja sobrescrever a string original

    free(quoted_str);  // Libera a memória alocada
}
char *process_quotes(const char **s) {
	const char *start;
	char quote;
	char *word;
	char *temp;
	int quotes;
   
	start = *s;
	word = NULL;
	quotes = is_quoted(*s);
   
	// Processa o primeiro trecho entre aspas ou sem aspas
	if (**s == '"' || **s == '\'') {
	    quote = *(*s)++; // Pula a primeira aspa
	    start = *s;
   
	    while (**s && **s != quote) {
		 (*s)++;
	    }
   
	    if (**s == quote) {
		 word = allocate_word(start, *s - start); // Extrai o conteúdo entre aspas
		 (*s)++; // Avança além da aspa final
	    }
	} else {
	    while (**s && !ft_strchr(" |<>", **s) && **s != '"' && **s != '\'') {
		 (*s)++;
	    }
	    word = allocate_word(start, *s - start); // Extrai a palavra sem aspas
	}
   
	// Processa trechos adicionais entre aspas ou sem aspas
	while (**s && !ft_strchr(" |<>", **s)) {
	    if (**s == '"' || **s == '\'') {
		 quote = *(*s)++; // Pula a aspa inicial
		 start = *s;
   
		 while (**s && **s != quote) {
		     (*s)++;
		 }
   
		 if (**s == quote) {
		     temp = allocate_word(start, *s - start); // Extrai o conteúdo entre aspas
		     (*s)++; // Avança além da aspa final
		 }
	    } else {
		 start = *s;
   
		 while (**s && !ft_strchr(" |<>", **s) && **s != '"' && **s != '\'') {
		     (*s)++;
		 }
   
		 temp = allocate_word(start, *s - start); // Extrai a palavra sem aspas
	    }
   
	    // Concatena o novo trecho com a palavra anterior
	    if (temp) {
		 char *joined = ft_strjoin(word, temp);
		 free(temp);
		 free(word);
		 word = joined;
	    }
	}
   
	if (quotes != 0) {
	    printf("removing quotes\n");
	    add_quote_type(word, quotes); // Adiciona o tipo de aspas, se necessário
	}
   
	return word;
   }


char	**tokenize(const char *s, char **envp)
{
	char	**array;
	int		i;

	while(*s && *s == ' ')
		s++;
	if (s == NULL || ft_count_word(s) == 0)
		return (NULL);
	i = 0;
	array = malloc((ft_count_word(s) + 1) * sizeof(char *));
	if (control_quotes(s) == 1)
		return (NULL);
	if (!array)
		return (NULL);
	process_words(&s, &array, &i, envp);
	array[i] = NULL;
	return (array);
}
