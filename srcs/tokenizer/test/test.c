/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 08:48:03 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/03 18:16:07 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "tokenizer.h"

void	print_tokens(t_list *list)
{
	t_token	*token;
	int		index;

	index = 1;
	while (list != NULL)
	{
		token = list->content;
		printf("    |token %d =[%s]->%d\n", index++, token->name, token->type);
		list = list->next;
	}
}

int	main(void)
{
	char	*line;
	t_list	*tokens;

	while (TRUE)
	{
		line = readline("-> ");
		tokens = tokenizer(line);
		print_tokens(tokens);
		free(line);
	}
}
