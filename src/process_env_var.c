#include "../headers/main.h"



// Para expandir múltiplas variáveis em um único input que contenha múltiplos $ (variáveis do ambiente), 
//será necessário implementar um processo de tokenização e substituição. Aqui está uma abordagem passo a passo para fazer isso:

// Passo 1: Identificar todas as ocorrências de $
// Iterar pelo input e localizar todos os símbolos $.
// Verificar o que vem logo após $. Pode ser uma sequência de caracteres alfanuméricos que define o nome da variável.

// Passo 2: Extrair os nomes das variáveis
// Quando encontrar um $, extraia o nome da variável que o segue.
// Pare no primeiro caractere que não seja válido para um nome de variável (por exemplo, um espaço ou outro símbolo).

// Passo 3: Substituir cada variável
// Para cada variável extraída, use a função getenv() para obter o valor correspondente no ambiente.
// Substitua o nome da variável (incluindo o $) pelo valor retornado por getenv().
// Mantenha o restante do texto intacto.

// Esse é um teste $B de variavéis $C de ambiente e valgrind $B $C
char	*replace_substring(char *string, char *replace_string, int index)
{

	char	*string_rest;
	char	*env_value;
	int	i;

	i = 0;
	string_rest = ft_substr(string, index + ft_strlen(replace_string) + 1, ft_strlen(string) - index);
	if (!string_rest)
		return (string);
	env_value = getenv(replace_string);
	if (!env_value)
		return (string);
	while (getenv(replace_string)[i])
	{
		string[index] = getenv(replace_string)[i];
		index++;
		i++;
	}
	string[index] = '\0';
	string = ft_strjoin(string, string_rest);
	if (!string)
		return(string);
	free(string_rest);
	return (string);
}
char	*process_env_var(char *input)
{
	int	index_of_env_symbol;
	int	start;
	int	i;
	int	end;
	int	temp;
	char	*word_to_switch;
	char	*input_to_return;

	index_of_env_symbol = 0;
	i = 0;
	while(input[index_of_env_symbol])
	{
		if (input[index_of_env_symbol] == '$')
		{
			start = index_of_env_symbol + 1;
			end = start;
			word_to_switch = ft_calloc((end - start + 2), sizeof(char));
			if (!word_to_switch)
				return (NULL);
			temp = start;
			while(ft_isalnum(input[end]))
				end++;	
			while (temp < end)
			{
				word_to_switch[i] = input[temp];
				temp++;
				i++;
			}
			word_to_switch[i] = '\0';
			input_to_return = replace_substring(input, word_to_switch, index_of_env_symbol);
			input = input_to_return;
			index_of_env_symbol = end - 1;
			free(word_to_switch);
		}
		index_of_env_symbol++;
		i = 0;
	}
	return(input);
}