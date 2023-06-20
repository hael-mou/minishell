/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:20:51 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/20 13:20:54 by oezzaou          ###   ########.fr       */
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
	if (analyzer(tokens) == NULL)
		return (clean_tokenizer(tokens), NULL);
	return (tokens);
}
