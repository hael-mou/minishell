/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:42:13 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/02 19:39:39 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//=== builtins_init ===========================================================
int	detect_nflag(char **args, int *index)
{
	char	*arg;
	int		nflag;

	nflag = TRUE;
	while (args && index && args[*index] && args[++(*index)][0] == '-')
	{
		arg = args[*index] + 1;
		while (*arg != 0)
		{
			if (*arg++ != 'n')
				return (nflag);
		}
		nflag = FALSE;
	}
	return (nflag);
}

//=== builtins_init ===========================================================
int	minishell_echo(char **args)
{
	int	index;
	int	nflag;

	index = (args && !ft_strcmp(*args, "echo")) - 1;
	if (args == NULL || args[index + 1] == NULL)
		return (SUCCESS);
	nflag = detect_nflag(args, &index);
	while (args[index] != NULL)
	{
		ft_putstr_fd(args[index++], 1);
		if (args[index] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (nflag == TRUE)
		ft_putstr_fd("\n", 1);
	return (SUCCESS);
}
