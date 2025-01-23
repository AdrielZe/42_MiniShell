/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:13:17 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/23 11:28:37 by victda-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#include "../../headers/tokenize.h"

void echo(t_tokens *tokens) {
	tokens = tokens->next;

    while (tokens)
	{
		if(tokens->type == TOKEN_ENV_VAR)
		{
			tokens-> value = process_env_var(tokens->value);
		}
        ft_putstr_fd(tokens->value, 1);
		ft_putstr_fd(" ", 1);
        tokens = tokens->next; // Avança para o próximo token na lista
    }
    printf("\n"); 
}