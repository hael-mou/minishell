/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:42:35 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/24 14:58:25 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	minishell_pwd(char **args)
{
	char	*abs_path;

	(void)args;
	abs_path = getcwd(NULL, 0);
	if (abs_path == NULL)
		return (FAILURE);
	printf("%s\n", abs_path);
	free(abs_path);
	return (SUCCESS);
}
