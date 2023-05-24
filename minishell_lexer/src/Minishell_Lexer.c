/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell_Lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:58:44 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/24 08:41:35 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*tokenizer(char *line)
{
	t_state	cur_state;
	t_state	prv_state;
	char	*cursor;

	prv_state = start;
	while (line != NULL)
	{
		cur_state = get_next_state(prv_state, *line);
		if (prv_state == start && cur_state == end)
			break;
		if (cur_state == end && prv_state != start)
		{
			create_token(NULL, cursor, line, prv_state);
			prv_state = start;
			continue ;
		}
		if (prv_state == start)
			cursor = line;
		prv_state = cur_state;
		line++;
	}
	return (NULL);
}
