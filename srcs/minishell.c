/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:26:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/26 20:37:32 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//=== minishell main ===========================================================
int	main(int argc, char **argv, char **env)
{
	t_minish	minish;

	minishell_init(env);
	minishell_ignore(argc, argv);
	while (TRUE)
	{
		g_sys.prompt = minishell_prompt();
		minish.input = readline(g_sys.prompt);
		if (minish.input == NULL)
			return (g_sys.exit_status);
		minish.tokens = lexer(minish.input);
		minish.tree = parser(minish.tokens);
		interpreter(minish.tree);
		if (minish.tree != NULL)
			add_history(minish.input);
		minishell_clean(&minish);
	}
	return (0);
}
