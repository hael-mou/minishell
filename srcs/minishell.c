/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:26:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/24 17:22:19 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//=== minishell main ===========================================================
int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_list	*tokens;
	t_node	*tree;
	char	*prompt;

	(void) argc;
	(void) argv;
	minishell_init(env);
	while (TRUE)
	{
		prompt =  minishell_prompt();
		input = readline(prompt);
		if (input == NULL)
			return (g_sys.exit_status);
		if (*input == 0)
			continue;
		tokens = lexer(input);
		if (!tokens)
			continue ;
		tree = parser(tokens);
		interpreter(tree);
		add_history(input);
		minishell_clean();
		free(input);
		free(prompt);
	}
	return (0);
}

//=== minishell init ===========================================================
void	minishell_init(char **env)
{
	g_sys.std_in = dup(STDIN_FILENO);
	g_sys.std_out = dup(STDOUT_FILENO);
	if (g_sys.std_in != ERROR && g_sys.std_out != ERROR)
	{
		minishell_export(env);
		// printf(CLEAR);
		// printf("%s\n", PROG_INFO);
		// printf("%s\n", DEVLOPERS);
		g_sys.pipeline.offset = -1;
		g_sys.pipeline.fd[0] = -1;
		g_sys.pipeline.fd[1] = -1;
		g_sys.merrno = -1;
		builtins_init(&g_sys.builtins);
		return ;
	}
	exit (ERROR);
}

//=== builtins_init ============================================================
void	builtins_init(t_built *builtins)
{
	builtins->name[0] = "echo";
	builtins->func[0] = minishell_echo;
	builtins->name[1] = "pwd";
	builtins->func[1] = minishell_pwd;
	builtins->name[2] = "env";
	builtins->func[2] = minishell_env;
	builtins->name[3] = "export";
	builtins->func[3] = minishell_export;
	builtins->name[4] = "unset";
	builtins->func[4] = minishell_unset;
	builtins->name[5] = "cd";
	builtins->func[5] = minishell_cd;
	builtins->name[6] = "exit";
	builtins->func[6] = minishell_exit;
	builtins->name[7] = "clear";
	builtins->func[7] = minishell_clear;
}

//=== minishell clear ==========================================================
void	minishell_clean(void)
{
	// 1 => destroy AST
	close(g_sys.pipeline.offset);
	g_sys.pipeline.offset = -1;
}
