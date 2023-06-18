/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:58:44 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/18 16:14:42 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

//=== tokenizer =============================================================== 
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
