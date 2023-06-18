/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:03:09 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/17 21:58:26 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//=== minishell export =========================================================
int	minishell_export(char *variable)
{
	t_list	*new_var;
	t_list	*select;

	new_var = create_variable(variable);
	if (new_var == NULL || invalid_name(get_var_content(new_var, "name")))
	{
		ft_lstdelone(new_var, clean_var);
		return (FAILURE);
	}
	select = ft_lstsearch(g_env, varcmp, get_var_content(new_var, "name"));
	if (g_env == NULL)
		g_env = new_var;
	else if (select != NULL)
	{
		clean_var(select->content);
		select->content = new_var->content;
		free(new_var);
	}
	else
		ft_lstlast(g_env)->next = new_var;
	return (SUCCESS);
}
