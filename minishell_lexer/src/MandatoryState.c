/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MandatoryState.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:57:40 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/21 14:19:02 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_state	st_start(char input)
{
	if (ft_isspace(input))
		return (start);
	if (input == '|')
		return (pipes);
	if (input == '<' || input == '>')
		return (st_redir(input, start));
	return (st_string(input, start));
}

t_state	st_string(char input, t_state prv_state)
{
	static char	quote;

	if (prv_state == quotes && input == quote)
		return (string);
	if (prv_state == quotes)
		return (quotes);
	if (input == '"' || input == '\'')
	{
		quote = input;
		return (quotes);
	}
	if (ft_strchr("\t |<>", input) == NULL)
		return (string);
	return (end);
}

t_state	st_redir(char input, t_state prv_state)
{
	static char	symbol;

	if (prv_state == redir && input == symbol)
		return (redir2);
	if (symbol == 0 && (input == '<' || input == '>'))
	{
		symbol = input;
		return (redir);
	}
	symbol = 0;
	return (end);
}
