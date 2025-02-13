/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:51:32 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/13 00:17:43 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void free_delimiters(t_delim *head)
{
	t_delim	*tmp;
	
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->delimiter);
		free(tmp);
	}
}

t_delim	*create_delim_list(char **delims)
{
	t_delim *head = NULL;
	t_delim *new;
	t_delim *last = NULL;
	int i = 0;

	while (delims[i])
	{
		new = malloc(sizeof(t_delim));
		if (!new)
			return (NULL);
		new->delimiter = strdup(delims[i]);
		new->next = NULL;
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return (head);
}