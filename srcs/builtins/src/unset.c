/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 14:52:54 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/17 19:18:41 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	minishell_unset(char *var_name)
{
	if (var_name != NULL)
	{
		ft_lstrmif(&g_env, var_name, varcmp, clean_var);
	}
	return (SUCCESS);
}