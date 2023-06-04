/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:04:53 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/03 18:33:45 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

//=== get_next_state ====================================================
int	get_next_state(int state, char *input)
{
	int	(*state_func[6])();

	if (*input == '\0' || state == SEMICOLON || state == AND || state == OR)
		return (END);
	if (state == OPEN_PARENTHESIS || state == CLOSE_PARENTHESIS)
		return (END);
	if (state == AND_IN_FUTURE)
		return (AND);
	state_func[START] = state_start;
	state_func[PIPE] = state_pipe;
	state_func[REDIR_OUT] = state_redout;
	state_func[REDIR_IN] = state_redin;
	state_func[SINGLE_QUOTES] = state_quates;
	state_func[DOUBLE_QUOTES] = state_quates;
	if (state < 6)
		return (state_func[state](input, state));
	return (state_string(input));
}

//=== set_state =========================================================
void	set_state(t_state *states, int index, char *key, int state)
{
	states[index].key = key;
	states[index].state = state;
}

//=== get_state =========================================================
int	get_state(t_state *states, int size, char input)
{
	int	index;

	index = -1;
	while (++index < size - 1)
	{
		if (ft_strchr(states[index].key, input) != NULL)
			return (states[index].state);
	}
	return (states[index].state);
}

//=== create_token ======================================================
t_token	*create_token(char *start, char *end, int type)
{
	t_token	*new_token;
	char	*name;

	new_token = malloc(sizeof(t_token));
	name = malloc(end - start + 1);
	if (new_token == NULL || name == NULL)
	{
		free(new_token);
		free(name);
		return (NULL);
	}
	new_token->name = name;
	new_token->type = type;
	while (start < end)
		*name++ = *start++;
	*name = 0;
	return (new_token);
}

//=== listadd_token =====================================================
t_list	*listadd_token(t_list **list, t_token *new_token)
{
	t_list	*new_node;

	new_node = ft_lstnew(new_token);
	if (new_token == NULL || new_node == NULL)
	{
		ft_lstclear(list, free);
		return (NULL);
	}
	ft_lstadd_back(list, new_node);
	return (*list);
}
