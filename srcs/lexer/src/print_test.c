/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:17:28 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/19 21:46:10 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdio.h>

char	*get_type(int type)
{
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == STRING)
		return ("STRING");
	if (type == HERE_DOC)
		return ("HERE_DOC");
	if (type == REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == SEMICOLON)
		return ("SEMICOLON");
	if (type == AND)
		return ("AND");
	if (type == OR)
		return ("OR");
	if (type == OPEN_PARENTHESIS)
		return ("OPEN_PARENTHESIS");
	if (type == CLOSE_PARENTHESIS)
		return ("CLOSE_PARENTHESIS");
	if (type == DOUBLE_QUOTES)
		return ("DOUBLE QUOTES");
	if (type == SINGLE_QUOTES)
		return ("SINGLE_QUOTES");
	return ("ERROR");
}

void	print_tokens(t_list	*tokens)
{
	t_token	*token;

	while (tokens != NULL)
	{
		token = tokens->content;
		printf("->token :\n");
		printf("	|token	:%s$\n", token->name);
		printf("	|type	:%s\n\n", get_type(token->type));
		tokens = tokens->next;
	}
}
