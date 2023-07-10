/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:04:34 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/02 19:34:10 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//=== builtins_init ===========================================================
/*void	builtins_init(char **built_name, t_func *built_func)
{
	built_name[0] = "echo";
	built_func[0] = minishell_echo;
	built_name[1] = "cd";
	built_func[1] = minishell_cd;
	built_name[2] = "pwd";
	built_func[2] = minishell_pwd;
	built_name[3] = "export";
	built_func[3] = minishell_export;
	built_name[4] = "unset";
	built_func[4] = minishell_unset;
	built_name[5] = "env";
	built_func[5] = minishell_env;
	built_name[6] = "exit";
	built_func[6] = minishell_exit;
}*/

//=== exec_builtins ===========================================================
/*int	exec_builtins(char *name, char **args)
{
	char	*built_name[7];
	t_func	built_func[7];
	int		index;

	index = -1;
	builtins_init(built_name, built_func);
	while (++index < 7)
	{
		if (ft_strcmp(name, built_name[index]) == 0)
		{
			return ((built_func[index])(args));
		}
	}
	return (FAILURE);
}*/
