/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:26:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/09 18:01:02 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	**expand_var(char *line);

//=== minishell main ====================================================
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_list	*tokens;
	t_node	*tree;

	(void) argc;
	(void) argv;
	minishell_init(env);
	while (TRUE)
	{
		input = readline("(🔞) ︻╦̵̵̿╤── 💥-> ");
		if (input == NULL)
			return (FAILURE);
		if (*input == 0)
			continue;
		tokens = lexer(input);
		tree = parser(tokens);
		interpreter(tree);
		printf("Done ...\n");
		minishell_clear();
		free(input);
	}
	return (0);
}

//=== minishell init ====================================================
void	minishell_init(char **env)
{
	g_sys.std_in = dup(STDIN_FILENO);
	g_sys.std_out = dup(STDOUT_FILENO);
	if (g_sys.std_in != ERROR && g_sys.std_out != ERROR)
	{
		minishell_export(env);
		printf(CLEAR);
		printf("%s\n", PROG_INFO);
		printf("%s\n\n", DEVLOPERS);
		g_sys.pipeline = -1;
		return ;
	}
	exit (ERROR);
}

//=== minishell clear ====================================================
void	minishell_clear(void)
{
	close(g_sys.pipeline);
	g_sys.pipeline = -1;
}
