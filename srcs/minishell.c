/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:26:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/27 11:40:08 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <signal.h>

//===========================================


void handler_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_sys.exit_status = 130;
		ft_putstr_fd("\n\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		minishell_prompt();
		rl_redisplay();
	}
}

void	minishell_signal(void)
{
	signal(SIGINT, &handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}


//=== minishell main ===========================================================
int	main(int argc, char **argv, char **env)
{
	t_minish	minish;

	minishell_init(env);
	minishell_ignore(argc, argv);
	minishell_signal();
	while (TRUE)
	{
		minish.input = readline(minishell_prompt());
		if (minish.input == NULL)
			return (g_sys.exit_status);
		minish.tokens = lexer(minish.input);
		minish.tree = parser(minish.tokens);
		interpreter(minish.tree);
		add_history(minish.input);
		minishell_clean(&minish);
	}
	return (0);
}
