/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:29:58 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/17 21:57:21 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "var.h"

//=== create variable node =====================================================
t_list	*create_variable(char *variable)
{
	t_list	*node;
	t_var	*new_var;

	node = ft_lstnew(NULL);
	new_var = ft_calloc(1, sizeof(t_var));
	if (variable == NULL || node == NULL || new_var == NULL)
	{
		return (free(node), free(new_var), NULL);
	}
	new_var->name = ft_strtok(variable, '=');
	if (new_var->name == NULL)
	{
		return (free(node), free(new_var), NULL);
	}
	variable += ft_toklen(variable, '=');
	if (*variable == 0)
		new_var->value = NULL;
	else
		new_var->value = ft_strdup(++variable);
	node->content = new_var;
	return (node);
}

//=== is invalid name =========================================================
int	invalid_name(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (TRUE);
	while (*(++name) != '\0')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (TRUE);
	}
	return (FALSE);
}

//=== get var content ===========================================================
char	*get_var_content(t_list *var_node, char *content)
{
	if (var_node != NULL && ft_strcmp(content, "name") == 0)
		return (((t_var *)var_node->content)->name);
	if (var_node != NULL && ft_strcmp(content, "value") == 0)
		return (((t_var *)var_node->content)->value);
	return (NULL);
}

//=== Varcmp ==================================================================
int	varcmp(void *value1, void *value2)
{
	if (ft_strcmp(((t_var *)value1)->name, value2) == 0)
	{
		return (TRUE);
	}
	return (FALSE);
}

//=== clean var ================================================================
void	clean_var(void *content)
{
	t_var	*var_node;

	var_node = content;
	free(var_node->name);
	free(var_node->value);
	free(var_node);
}
