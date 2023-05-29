/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:48:55 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/29 17:30:48 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	shell_env(void)
{
    t_list	*env_tmp;
	t_var	*var;

	env_tmp = env;
	while (env_tmp != NULL)
	{
		var = env_tmp->content;
		printf("%s=%s\n", var->key, var->value);
		env_tmp = env_tmp->next;
	}
}
