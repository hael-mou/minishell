/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:00:40 by oezzaou           #+#    #+#             */
/*   Updated: 2023/05/29 19:39:38 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_var(char *key, char *value)
{
	t_list	*select;

	if (env == NULL)
		env = ft_lstnew(new_var(key, value));
	else
	{
		select = get_var(key);
		if (select == NULL)
		{
			select = ft_lstlast(env);
			select->next = ft_lstnew(new_var(key, value));
			return ;
		}
		free(select->content);
		select->content = new_var(key, value);
	}
}

int	shell_export(char *new_var)
{
	char	*key;
	char	*value;

	key = extract_key(new_var);
	// check if valid varable
	value = extract_value(new_var);
	export_var(key, value);
	return (SUCCESS);
}

void	export_show(void)
{
	t_list	*env_tmp;
	t_var	*var;

	env_tmp = env;
	while (env_tmp != NULL)
	{
		var = env_tmp->content;
		printf("declare -x ");
		printf("%s=\"%s\"\n", var->key, var->value);
		env_tmp = env_tmp->next;
	}
}
