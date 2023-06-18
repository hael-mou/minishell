/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:45:47 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/18 15:21:11 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// //=== is_end_of_command =================================================
// int	is_end_of_command(t_list *token)
// {
// 	int	type;

// 	type = get_token_type(token);
// 	if (type == PIPE || type == SEMICOLON || type == OPEN_PARENTHESIS)
// 		return (TRUE);
// 	if (type == CLOSE_PARENTHESIS || type == AND || type == OR)
// 		return (TRUE);
// 	return (FALSE);
// }

// //=== is_redirection ====================================================
// int	is_redirection(t_list *token)
// {
// 	int	type;

// 	type = get_token_type(token);
// 	if (type == REDIR_IN || type == HERE_DOC)
// 		return (TRUE);
// 	if (type == REDIR_OUT || type == REDIR_APPEND)
// 		return (TRUE);
// 	return (FALSE);
// }

// //=== get_argument ======================================================
// char	**get_argument(t_list *tokens)
// {
// 	char	**table;
// 	char	*arg;

// 	table = ft_calloc(2, sizeof(char *));
// 	arg = ft_strdup("");
// 	if (table == NULL || arg == NULL)
// 		return (free(table), free(arg), NULL);
// 	while (tokens != NULL)
// 	{
// 		// join token
// 	}
// }

// //=== extract_files =====================================================
// t_list	*extract_files(t_list *tokens)
// {
// 	t_list	*files;

// 	while (tokens != NULL && is_end_of_command(tokens) == FALSE)
// 	{
// 		if (is_redirection(tokens) == TRUE)
// 		{
// 			listadd_file(&files, create_file(tokens, tokens->next));
// 			if (files == NULL || tokens->next == NULL)
// 			{
// 				ft_lstclear(&files, clean_file);
// 				return (NULL);
// 			}
// 			tokens = tokens->next;
// 		}
// 		tokens = tokens->next;
// 	}
// 	return (files);
// }
