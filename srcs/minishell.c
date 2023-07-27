/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:26:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/27 10:25:34 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <signal.h>

//===========================================


void handler_sigint(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
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
		g_sys.prompt = minishell_prompt();
		minish.input = readline(g_sys.prompt);
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
