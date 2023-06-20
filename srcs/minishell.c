/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:26:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/20 13:11:21 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//=== minishell main ====================================================
int	main(int argc, char **argv, char **env)
{
	char	*cmd_line;
	t_list	*tokens;
	//t_node	*tree;

	(void) argc;
	(void) argv;
	minishell_init(env);
	while (TRUE)
	{
		cmd_line = readline(" (🔞) ︻╦̵̵̿╤── 💥->  ");
		if (cmd_line == NULL)
			return (FAILURE);
		tokens = lexer(cmd_line);
		//tree = parser(tokens);
//		interpreter(tree);
		print_tokens(tokens);
		clean_tokenizer(tokens);
		free(cmd_line);
	}
	return (0);
}
