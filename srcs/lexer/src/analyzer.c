/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 23:48:04 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/19 11:13:00 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analyzer.h"

//=== analyzer ==========================================
t_list	*analyzer(t_list *tokens)
{
	t_list		*cursor;
	int			cur_state;
	int			prev_state;
	int			*data;

	data = (int [3]){0, 0, 0};
	cursor = tokens;
	prev_state = START;
	while (cursor)
	{
		cur_state = get_current_state(cursor);
		update_data(data, cur_state);
		if (parse_error(prev_state, cur_state, cursor, data) == PARSE_ERROR)
			return (NULL);
		if (cursor->next == NULL)
			cursor->next = complete_tokens(data, get_token_type(cursor));
		prev_state = cur_state;
		cursor = cursor->next;
	}
	return (tokens);
}
