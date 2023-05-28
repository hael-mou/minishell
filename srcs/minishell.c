/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:44:47 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/28 20:27:57 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
    (void) env;
    //init minishell
	while (TRUE)
	{
		//1 => read command
		//2 => pars command line
		//3 => exec commands
        //4 => add to history
		//4 => clear all
	}
	return (EXIT_SUCCESS);
}