/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:26:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/25 06:41:23 by hael-mou         ###   ########.fr       */
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
		tokens = lexer(input);
		tree = parser(tokens);
		interpreter(tree);
		char **t = expand_var(input);
		while (t != NULL && *t != NULL)
		{
			printf("%s\n", *t);
			t++;
		}
		free(input);
	}
	minishell_clear();
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
		return ;
	}
	exit (ERROR);
}

//=== minishell clear ====================================================
void	minishell_clear(void)
{
}
