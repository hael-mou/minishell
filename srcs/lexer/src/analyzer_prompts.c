/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_prompts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:19:51 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/20 13:19:58 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "analyzer.h"

//=== operator_prompt ===================================
t_list	*operator_prompt(int type)
{
	char	*prompt;
	char	*line;
	t_list	*new_tokens;

	new_tokens = NULL;
	prompt = get_prompt(type);
	while (!new_tokens)
	{
		line = readline(prompt);
		new_tokens = tokenizer(line);
		free(line);
	}
	return (new_tokens);
}

//=== subsh_prompt ======================================
t_list	*subsh_prompt(int eq_point)
{
	t_list	*new_tokens;
	int		subshs;
	char	*line;

	new_tokens = NULL;
	while (!new_tokens)
	{
		subshs = eq_point;
		while (--subshs > 0)
			printf("%-6.5s", SUBSH_PROMPT);
		line = readline(SUBSH_PROMPT);
		new_tokens = tokenizer(line);
		free(line);
	}
	return (new_tokens);
}

//=== quote_prompt ======================================
t_list	*quote_prompt(t_list *token)
{
	char	*line;
	char	*set;
	char	*tokens_part;
	char	*content_part;
	t_list	*new_tokens;

	set = "'\"";
	line = ft_strdup("");
	while (!ft_strchr(line, set[get_token_type(token) - 4]))
		line = ft_strjoin(line, readline(get_prompt(get_token_type(token))));
	tokens_part = ft_strchr(line, set[get_token_type(token) - 4]) + 1;
	content_part = ft_substr(line, 0, tokens_part - line);
	set_token_name(token, ft_strjoin(get_token_name(token), content_part));
	set_token_type(token, STRING);
	new_tokens = tokenizer(tokens_part);
	free(line);
	return (new_tokens);
}

//=== get_prompt ========================================
char	*get_prompt(int type)
{
	if (type == PIPE)
		return (PIPE_PROMPT);
	if (type == AND)
		return (AND_PROMPT);
	if (type == OR)
		return (OR_PROMPT);
	if (type == SINGLE_QUOTES)
		return (QUOTE_PROMPT);
	if (type == DOUBLE_QUOTES)
		return (DQUOTE_PROMPT);
	return (NULL);
}
