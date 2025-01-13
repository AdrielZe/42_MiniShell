/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:28:59 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/13 17:25:03 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <readline/readline.h> //readline
# include <readline/history.h> //readline history
# include "../libft/libft.h" //libft

char	*process_env_var(char *input);
char	**tokenize(char const *s, char c);

#endif