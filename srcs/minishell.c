/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:26:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/18 19:26:04 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//=== minishell main ====================================================
int	main(int number_arg, char **argument, char **env)
{
	char	*cmd_line;
	t_list	*tokens;
	t_node	*tree;

	(void)number_arg;
	(void)argument;
	minishell_init(env);
	minishell_info();
	while (TRUE)
	{
		cmd_line = readline(" (🔞 ) ︻╦̵̵̿╤── ->  ");
		if (cmd_line == NULL)
			return (FAILURE);
		tokens = lexer(cmd_line);
		tree = parser(tokens);
//		interpreter(tree);
//		print_tokens(tokens);
		clean_tokenizer(tokens);
		free(cmd_line);
	}
	return (0);
}
