/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:42:47 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/22 15:33:50 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//=== show export =========================================================
void	export_show(void)
{
	t_list	*cursor;
	char	*name;
	char	*value;

	cursor = g_sys.env;
	while (cursor != NULL)
	{
		name = get_var_name(cursor);
		if (ft_strcmp(name, "_") != 0)
		{
			value = get_var_value(cursor);
			printf("declare -x %s", name);
			if (value != NULL)
				printf("=\"%s\"", value);
			printf("\n");
		}
		cursor = cursor->next;
	}
}

//=== minishell export =========================================================
int	minishell_export(char **args)
{
	int	index;
	int	status;

	status = 0;
	index = (args && !ft_strcmp(*args, "export")) - 1;
	if (args == NULL || args[index + 1] == NULL)
	{
	//	export_show();
		return (SUCCESS);
	}
	while (args[++index] != NULL)
		status += set_variable(&g_sys.env, args[index]);
	return ((status == index - !ft_strcmp(*args, "export")));
}
