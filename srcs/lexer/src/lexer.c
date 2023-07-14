/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:20:51 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/14 19:21:59 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//=== Lexer ====================================================================
t_list	*lexer(char *line)
{
	t_list	*tokens;

	tokens = tokenizer(line);
	if (analyzer(tokens) == NULL)
		return (clean_tokenizer(tokens), NULL);
	return (tokens);
}

//=== tokenizer ================================================================
t_list	*tokenizer(char *line)
{
	int		cur_state;
	int		prv_state;
	t_list	*tokens;
	char	*cursor;

	prv_state = START;
	tokens = NULL;
	while (line != NULL)
	{
		cur_state = get_next_state(prv_state, line);
		if (prv_state == START && cur_state == END)
			break ;
		if (cur_state == END && prv_state != START)
		{
			if (!listadd_token(&tokens, create_token(cursor, line, prv_state)))
				return (NULL);
			prv_state = START;
			continue ;
		}
		if (prv_state == START)
			cursor = line;
		prv_state = cur_state;
		line++;
	}
	return (tokens);
}

//=== analyzer =================================================================
t_list	*analyzer(t_list *tokens)
{
	t_list		*cursor;
	int			cur_state;
	int			prev_state;
	int			eq_point;

	eq_point = 0;
	cursor = tokens;
	prev_state = START;
	while (cursor)
	{
		cur_state = get_current_state(cursor);
		eq_point += (cur_state == OPEN_PARENTHESIS);
		eq_point -= (cur_state == CLOSE_PARENTHESIS);
		if (parse_error(prev_state, cur_state, cursor, eq_point) == PARSE_ERROR)
			return (NULL);
		if (cursor->next == NULL)
			cursor->next = complete_tokens(cursor, eq_point);
		prev_state = cur_state;
		cursor = cursor->next;
	}
	return (tokens);
}
