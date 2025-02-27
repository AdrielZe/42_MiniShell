/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:01:53 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/27 16:02:20 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void *gc_malloc(size_t size, t_shell *shell)
{
    void        *ptr;
    t_garbage   *new_node;

    ptr = malloc(size);
    if (!ptr)
        return (NULL);
    new_node = malloc(sizeof(t_garbage));
    if (!new_node)
    {
        free(ptr);
        return (NULL);
    }
    new_node->ptr = ptr;
    new_node->next = shell->gc;
    shell->gc = new_node;
    return (ptr);
}

void gc_free(t_shell *shell)
{
    t_garbage *temp;

    while (shell->gc)
    {
        temp = shell->gc;
        free(temp->ptr);
        shell->gc = shell->gc->next;
        free(temp);
    }
}
