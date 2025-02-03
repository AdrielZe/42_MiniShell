/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:04:26 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/03 20:31:18 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count_tokens(char *command)
{
    int count = 0;
    char *token = strtok(command, " ");

    while (token)
    {
        count++;
        token = strtok(NULL, " ");
    }
    return count;
}
char **split_command(char *command)
{
    char **args;
    char *token;
    int i = 0;
    int j = 0;

    args = malloc(sizeof(char *) * (count_tokens(command) + 1)); // count_tokens deve contar quantos argumentos são esperados
    if (!args)
        return NULL;
	
	 printf("command: %s\n", command);
    token = strtok(command, " ");
    while (token != NULL)
    {
        args[i] = strdup(token);  // Copia cada argumento para o array
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;  // O último argumento deve ser NULL, como esperado por execvp
    while (args[j])
    {
	printf("%s\n", args[j]);
	j++;
    }
    return args;
}
