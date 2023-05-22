/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell_Lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:58:44 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/22 09:14:55 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

t_state	get_next_state(t_state state, char input)
{
	if (state == start)
		return (st_start(input));
	if (state == redir || state == redir2)
		return (st_redir(input, state));
	if (state == pipes)
		return (end);
	return (st_string(input, state));
}

void	create_token(t_list **list, char *start, char *end, t_state type)
{
	while (start < end)
	{
		printf("%c", *start);
		start++;
	}
	printf("$ -> %u\n", type);
}

t_list	*tokenizer(char *line)
{
	t_list	*tokens;
	t_state	cur_state;
	t_state	prv_state;
	char	*t_start;

	tokens = NULL;
	prv_state = start;
	while (line != NULL)
	{
		cur_state = get_next_state(prv_state, *line);
		if (prv_state == start && cur_state != start)
			t_start = line;
		else if (cur_state == end || *line == '\0')
		{
			create_token(&tokens, t_start, line, prv_state);
			prv_state = start;
			continue ;
		}
		line++;
	}
	return (NULL);
}
