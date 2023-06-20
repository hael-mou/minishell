/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:26:25 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/20 19:35:20 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//=== minishell main ====================================================
int	main(int argc, char **argv, char **env)
{
	char	*cmd_line;
	t_list	*tokens;
	t_command	*tree;

	(void) argc;
	(void) argv;
	minishell_init(env);
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
