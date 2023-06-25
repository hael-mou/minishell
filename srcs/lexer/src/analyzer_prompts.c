/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_prompts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:19:51 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/22 23:55:44 by hael-mou         ###   ########.fr       */
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
	int		*data;
	void	*tmp;
	t_list	*new_tokens;

	line = get_token_name(token);
	data = (int [3]){get_token_type(token), 0, 0};
	update_quotes_data(line, data);
	while (data[SQUOTES] % 2 || data[DQUOTES] % 2)
	{
		tmp = readline(get_prompt(data[TYPE]));
		update_quotes_data((char *)tmp, data);
		line = ft_strjoin(line, (char *)tmp);
	}
	tmp = tokenizer(line);
	new_tokens = ((t_list *)tmp)->next;
	set_token_name(token, ft_strdup(get_token_name(tmp)));
	set_token_type(token, STRING);
	ft_lstdelone(tmp, free_token);
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
