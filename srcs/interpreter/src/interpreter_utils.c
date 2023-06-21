/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:16:20 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/21 13:17:48 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

char	**get_env(t_list *g_env)
{
	char	**env;
	int		i;

	env = malloc(sizeof(char *) * (ft_lstsize(g_env) + 1));
	if (env)
		return (NULL);
	i = 0;
	while (g_env)
	{
		env[i++] = ft_strdup((char *) g_env->content);
		g_env = g_env->next;
	}
	env[i] = NULL;
	return (env);
}
