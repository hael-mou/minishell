/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_state2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:57:40 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/03 17:54:08 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

//=== state_pipe =========================
int	state_pipe(char *input)
{
	if (*input == '|' && BONUS == TRUE)
		return (OR);
	return (END);
}

//=== state_redout =======================
int	state_redout(char *input)
{
	if (*input == '>')
		return (REDIR_APPEND);
	return (END);
}

//=== state_redin ========================
int	state_redin(char *input)
{
	if (*input == '<')
		return (HERE_DOC);
	return (END);
}
