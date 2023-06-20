/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:26:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/20 15:25:59 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//=== minishell main ====================================================
int	main(int number_arg, char **argument, char **env)
{
	char	*cmd_line;
	t_list	*tokens;
	t_command	*tree;

	(void)number_arg;
	(void)argument;
	minishell_init(env);
	minishell_info();
	while (TRUE)
	{
		cmd_line = readline(" (🔞) ︻╦̵̵̿╤── 💥-> ");
		if (cmd_line == NULL)
			return (FAILURE);
		tokens = lexer(cmd_line);
		print_tokens(tokens);
		// tree = (t_command *)parser(tokens);
		// interpreter(tree);
		// printf("%s\n", tree->name);
		// t_list *files;

		// files = NULL;
		// files = tree->in_out;
		// printf("%p\n", files);
		// while (files != NULL)
		// {
		// 	printf("name = %s, type = %d\n", get_file_name(files), get_file_type(files));
		// 	files = files->next;
		// }
		clean_tokenizer(tokens);
		free(cmd_line);
	}
	return (0);
}
