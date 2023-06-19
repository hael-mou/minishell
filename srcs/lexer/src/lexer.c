/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:41:23 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/19 09:26:03 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//=== Lexer =============================================
t_list	*lexer(char *line)
{
	t_list	*tokens;

	tokens = tokenizer(line);
	if (tokens == NULL)
		return (NULL);
	if (analyzer(tokens) == NULL)
	{
		clean_tokenizer(tokens);
		return (NULL);
	}
	return (tokens);
}
