/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:48:06 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/17 23:40:40 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_info(void)
{
	printf("\033[2J\033[H");
	printf("%s\n", PROGRAM_INFO);
	printf("%s\n\n", DEVLOPERS);
}

void	minishell_init(char **env)
{
	while (env && *env)
	{
		minishell_export(*env++);
	}
}
