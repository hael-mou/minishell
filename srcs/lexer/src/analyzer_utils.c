/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:05:13 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/19 11:49:57 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analyzer.h"

//=== get_current_state =================================
int	get_current_state(t_list *token)
{
	int	type;

	type = get_token_type(token);
	if (state_operator(token) == OPERATOR)
		return (OPERATOR);
	if (state_redir(token) == REDIR)
		return (REDIR);
	if (type == CLOSE_PARENTHESIS || type == OPEN_PARENTHESIS)
		return (type);
	if (type == DOUBLE_QUOTES || type == SINGLE_QUOTES)
		return (type);
	if (type == SEMICOLON)
		return (type);
	return (STRING);
}

//=== update_data ======================================
void	update_data(int *data, int cur_state)
{
	data[EQ_POINT] += (cur_state == OPEN_PARENTHESIS);
	data[EQ_POINT] -= (cur_state == CLOSE_PARENTHESIS);
	if ((cur_state == SINGLE_QUOTES || cur_state == DOUBLE_QUOTES)
		&& data[QUOTE_TYPE] == 0)
		data[QUOTE_TYPE] = cur_state;
	if (cur_state == data[QUOTE_TYPE])
		data[QUOTES]++;
}

//=== parse_error =======================================
int	parse_error(int prev_state, int state, t_list *token, int *data)
{
	char	*msg;

	msg = NULL;
	if ((!token->next && state == REDIR))
		msg = "newline";
	if ((prev_state == START && state == OPERATOR)
		|| (prev_state == OPERATOR && state == OPERATOR)
		|| (prev_state == OPEN_PARENTHESIS && state == OPERATOR)
		|| (prev_state == OPEN_PARENTHESIS && state == CLOSE_PARENTHESIS)
		|| (prev_state == OPERATOR && state == CLOSE_PARENTHESIS)
		|| (prev_state == REDIR && state == REDIR)
		|| (prev_state == REDIR && state == OPERATOR)
		|| (data[EQ_POINT] < 0))
		msg = get_token_name(token);
	if (prev_state == STRING && state == OPEN_PARENTHESIS)
		msg = get_token_name(token->next);
	if (msg)
	{
		ft_putstr_fd(PARSE_ERROR_MSG, 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (PARSE_ERROR * !(!msg));
}

//=== complete_tokens ===================================
t_list	*complete_tokens(int *data, int type)
{
	if (type == PIPE || type == AND || type == OR)
		return (operator_prompt(type));
	if (data[QUOTES] % 2)
		return (quote_prompt(data));
	if (data[EQ_POINT] > 0)
		return (subsh_prompt(data));
	return (NULL);
}
