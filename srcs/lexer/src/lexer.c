/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:41:23 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/18 17:13:26 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//=== Lexer =============================================
t_list	*lexer(char *line)
{
	t_list	*tokens;

	tokens = tokenizer(line);
	if (!tokens)
		return (NULL);
	if (!analyzer(tokens))
		return (ft_lstclear(&tokens, free), NULL);
	return (tokens);
}
