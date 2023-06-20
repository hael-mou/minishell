/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:44:32 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/19 21:39:55 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

//=== create_token ======================================================
t_token	*create_token(char *start, char *end, int type)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->type = type;
	new_token->name = ft_substr(start, 0, (end - start));
	if (new_token->name == NULL)
	{
		free(new_token);
		new_token = NULL;
	}
	return (new_token);
}

//=== free_token =====================================================
void	free_token(void *content)
{
	t_token	*token;

	token = content;
	if (token != NULL)
		free(token->name);
	free(token);
}

//=== listadd_token =====================================================
t_list	*listadd_token(t_list **list, t_token *new_token)
{
	t_list	*new_node;

	new_node = ft_lstnew(new_token);
	if (new_token == NULL || new_node == NULL)
	{
		ft_lstclear(list, free_token);
		return (NULL);
	}
	ft_lstadd_back(list, new_node);
	return (*list);
}

//=== get_token_name ====================================================
char	*get_token_name(t_list *token)
{
	if (token != NULL)
		return (((t_token *)token->content)->name);
	return (NULL);
}

//=== get_token_type ====================================================
int	get_token_type(t_list *token)
{
	if (token != NULL)
		return (((t_token *)token->content)->type);
	return (0);
}

//=== set_token_name ====================================================
void	set_token_name(t_list *token, char *new_name)
{
	((t_token *)token->content)->name = new_name;
}

//=== set_token_type ====================================================
void	set_token_type(t_list *token, int new_type)
{
	((t_token *)token->content)->type = new_type;
}
