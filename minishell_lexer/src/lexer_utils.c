/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:42:28 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/24 09:34:00 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_state	get_next_state(t_state state, char input)
{
	t_state_func	state_func[4];

	state_func[start] = st_start;
	state_func[redir] = st_redir;
	state_func[redir2] = st_redir;
	state_func[pipes] = st_pipes;
	if (state < 4)
		return (state_func[state](input, state));
	return (st_string(input, state));
}

void	create_token(t_list **list, char *start, char *end, t_state type)
{
}

void	print_tokens(t_list *list)
{
}
