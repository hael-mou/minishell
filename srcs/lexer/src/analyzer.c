/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:20:17 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/20 13:21:29 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analyzer.h"

//=== analyzer ==========================================
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
