/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:29:27 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/19 18:39:34 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_space(char c) {
	return (c == ' ' || c == '\t');
}

int count_words(const char *s) {
	int count = 0;
	int in_quotes = 0;
	char quote_char = 0;

	while (*s) {
		while (is_space(*s))
			s++;
		if (*s == '\0')
			break;
		if (*s == '"' || *s == '\'') {
			quote_char = *s++;
			in_quotes = 1;
			while (*s && (*s != quote_char))
				s++;
			if (*s == quote_char)
				s++;
		} else {
			while (*s && !is_space(*s) && *s != '"' && *s != '\'')
				s++;
		}
		count++;
	}
	return count;
}

char *extract_word(const char **s) {
	char *word;
	int len = 0;
	int in_quotes = 0;
	char quote_char = 0;
	const char *start = *s;

	if (**s == '"' || **s == '\'') {
		quote_char = **s;
		start++;
		(*s)++;
		in_quotes = 1;
		while (**s && **s != quote_char) {
			(*s)++;
			len++;
		}
		if (**s == quote_char)
			(*s)++;
	} else {
		while (**s && !is_space(**s) && **s != '"' && **s != '\'') {
			(*s)++;
			len++;
		}
	}
	word = (char *)malloc(len + 1);
	if (!word)
		return NULL;
	strncpy(word, start, len);
	word[len] = '\0';
	return word;
}

char **split_with_quotes(const char *s) {
	int i = 0;
	char **result;
	int words = count_words(s);

	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return NULL;
	while (*s) {
		while (is_space(*s))
			s++;
		if (*s == '\0')
			break;
		result[i++] = extract_word(&s);
	}
	result[i] = NULL;
	return result;
}
