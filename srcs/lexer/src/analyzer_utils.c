/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:20:35 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/10 11:28:26 by oezzaou          ###   ########.fr       */
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

//=== parse_error =======================================
int	parse_error(int prev_state, int state, t_list *token, int eq_point)
{
	char	*msg;

	msg = NULL;
	if ((prev_state == START && state == OPERATOR)
		|| (prev_state == OPERATOR && state == OPERATOR)
		|| (prev_state == CLOSE_PARENTHESIS && state == STRING)
		|| (prev_state == OPEN_PARENTHESIS && state == OPERATOR)
		|| (prev_state == OPERATOR && state == CLOSE_PARENTHESIS)
		|| (prev_state == OPEN_PARENTHESIS && state == CLOSE_PARENTHESIS)
		|| (prev_state == CLOSE_PARENTHESIS && state == OPEN_PARENTHESIS)
		|| (prev_state == REDIR && state == REDIR)
		|| (prev_state == REDIR && state == OPERATOR)
		|| (eq_point < 0))
		msg = get_token_name(token);
	if ((prev_state == STRING && state == OPEN_PARENTHESIS)
		|| (!token->next && state == REDIR))
	{
		msg = get_token_name(token->next);
		if (!msg)
			msg = "newline";
	}
	if (msg != NULL)
		ft_print_error(PARSE_ERROR_MSG"%'\n", msg);
	return (PARSE_ERROR * !(!msg));
}

//=== complete_tokens ===================================
t_list	*complete_tokens(t_list *token, int eq_point)
{
	int		type;
	t_list	*new_tokens;

	new_tokens = NULL;
	type = get_token_type(token);
	if (type == PIPE || type == AND || type == OR)
		return (operator_prompt(type));
	if (type == SINGLE_QUOTES || type == DOUBLE_QUOTES)
	{
		new_tokens = quote_prompt(token);
		if (new_tokens != NULL)
			return (new_tokens);
	}
	if (eq_point > 0)
		ft_lstadd_back(&new_tokens, subsh_prompt(eq_point));
	return (new_tokens);
}

//=== update_quotes_data ================================
void	update_quotes_data(char *buff, int *data)
{
	char	*set;
	int		i;

	set = "'\"";
	i = -1;
	while (buff[++i])
	{
		if (buff[i] == set[-data[TYPE] + 5] && (data[data[TYPE] - 3] % 2 == 0))
			data[TYPE] = -data[TYPE] + 9;
		if (buff[i] == set[0] && data[TYPE] == SINGLE_QUOTES)
			data[SQUOTES]++;
		if (buff[i] == set[1] && data[TYPE] == DOUBLE_QUOTES)
			data[DQUOTES]++;
	}
}
