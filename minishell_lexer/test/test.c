/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:00:02 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/22 09:07:58 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include "lexer.h"

int	main(void)
{
	char	*line;
	t_list	*tokens;

	while (TRUE)
	{
		line = readline("-> ");
		tokens = tokenizer(line);
		free(line);
	}
}
