/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 08:48:03 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/27 09:53:50 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "lexer.h"

char    *get_type(t_state type)
{
    if (type == start)
        return ("start");
    if (type == redir)
        return ("redir");
    if (type == redir2)
        return ("redir2");
    if (type == pipes)
        return ("pipes");
    if (type == string)
        return ("string");
    if (type == quotes)
        return ("quotes error");
    return ("error");
}

void    print_tokens(t_list *list)
{
    t_token *token;
    char    *type;
    int     index;

    index = 1;
    while (list != NULL)
    {
        token = list->content;
        type = get_type(token->type);
        printf("    |token %d =[%s]->%s\n", index, token->name, type);
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
