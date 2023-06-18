/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:37:46 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/18 09:22:05 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
//=== minishell main ====================================================
int	main(int number_arg, char **argument, char **env)
{
	char	*cmd_line;
	
	(void)number_arg;
	(void)argument;
	minishell_init(env);
	minishell_info();
	while (TRUE)
	{
		cmd_line = readline("🔞 - ");
		if (cmd_line == NULL)
			return (FAILURE);
		t_list *tokens = tokenizer(cmd_line);
		print_tokens(tokens);
		clean_tokenizer(tokens);
		free(cmd_line);
	}
	return (0);
}
