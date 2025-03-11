/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:57:59 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/10 19:15:04 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

static pid_t heredoc_pid = -1;

int* get_heredoc_status(void)
{
    static int heredoc_status = 0;  // A variável estática persiste entre chamadas
    return &heredoc_status;         // Retorna o endereço da variável
}

void set_heredoc_status(int status)
{
    *get_heredoc_status() = status;  // Altera o valor da variável estática
}
