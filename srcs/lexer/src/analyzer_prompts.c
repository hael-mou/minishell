/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_prompts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:08:46 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/18 17:10:50 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analyzer.h"

//=== operator_prompt ===================================
t_list	*operator_prompt(int type)
{
	t_list	*new_tokens;
	char	*line;

	if (type == PIPE)
		line = readline(PIPE_PROMPT);
	if (type == AND)
		line = readline(AND_PROMPT);
	if (type == OR)
		line = readline(OR_PROMPT);
	new_tokens = tokenizer(line);
	free(line);
	return (new_tokens);
}

//=== subsh_prompt ======================================
t_list	*subsh_prompt(int *data)
{
	t_list	*new_tokens;
	int		subshs;
	char	*line;

	subshs = data[EQ_POINT];
	while (--subshs > 0)
		printf("%-6.5s", SUBSH_PROMPT);
	line = readline(SUBSH_PROMPT);
	new_tokens = tokenizer(line);
	free(line);
	return (new_tokens);
}

//=== quote_prompt ======================================
t_list	*quote_prompt(int *data)
{
	t_list	*new_tokens;
	char	*line;

	if (data[QUOTE_TYPE] == DOUBLE_QUOTES)
		line = readline(DQUOTE_PROMPT);
	if (data[QUOTE_TYPE] == SINGLE_QUOTES)
		line = readline(QUOTE_PROMPT);
	new_tokens = tokenizer(line);
	free(line);
	return (new_tokens);
}
