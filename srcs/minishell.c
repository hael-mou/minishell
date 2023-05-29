/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 12:44:47 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/29 19:33:09 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_init(char	**env_var)
{
	while (env_var && *env_var)
	{
		if (shell_export(*env_var++) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

void	display_shell_info(void)
{
	printf("\033[2J""\033[H");
	printf("\033[3;37m\n%s\n", PROGRAM_INFO);
	printf("%s\n", DEVLOPERS);
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
    if (minishell_init(env) == SUCCESS)
	{
		//display_shell_info();
		shell_export("PATH=TST");
		t_var *test = get_var("PATH")->content;
		printf("%s\n", test->value);
		//shell_env();
		while (TRUE)
		{
			//1 => read command
			//2 => pars command line
			//3 => exec commands
        	//4 => add to history
			//4 => clear all
		}
	}
	return (EXIT_SUCCESS);
}
