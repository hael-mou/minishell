/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:45:47 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/22 14:35:38 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//=== is_end_of_command =================================================
int	is_end_of_command(t_list *token)
{
	int	type;

	type = get_token_type(token);
	if (!token || type == CLOSE_PARENTHESIS || type == AND || type == OR)
		return (TRUE);
	if (type == PIPE || type == SEMICOLON || type == OPEN_PARENTHESIS)
		return (TRUE);
	return (FALSE);
}

//=== is_redirection ====================================================
int	is_redirection(t_list *token)
{
	int	type;

	type = get_token_type(token);
	if (type == REDIR_IN || type == HERE_DOC)
		return (TRUE);
	if (type == REDIR_OUT || type == REDIR_APPEND)
		return (TRUE);
	return (FALSE);
}

//=== get_argument ======================================================
char	*join_argument(t_list *tokens)
{
	char	*arg;

	arg = ft_strdup("");
	if (arg == NULL)
		return (free(arg), NULL);
	while (is_end_of_command(tokens) == FALSE)
	{
		if (is_redirection(tokens) == TRUE)
		{
			if (tokens->next == NULL)
				return (free(arg), NULL);
			tokens = tokens->next->next;
			continue ;
		}
		arg = ft_vstrjoin(3, arg, get_token_name(tokens), S_SPACE);
		tokens = tokens->next;
	}
	return (arg);
}

//=== extract_files =====================================================
t_list	*extract_files(t_list *tokens)
{
	t_list	*files;
	char	*name;
	int		type;

	files = NULL;
	while (is_end_of_command(tokens) == FALSE)
	{
		if (is_redirection(tokens) == TRUE)
		{
			type = get_token_type(tokens);
			name = get_token_name(tokens->next);
			listadd_file(&files, create_file(name, type));
			if (files == NULL || tokens->next == NULL)
			{
				ft_lstclear(&files, clean_file);
				return (NULL);
			}
			if (get_file_type(files) == HERE_DOC)
				run_heredoc(files);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (files);
}

//=== clean tree ========================================================
void	clean_tree(t_node *head)
{
	int	node_type;

	if (head != NULL)
	{
		node_type = get_node_type(head);
		if (node_type != COMMAND)
		{
			clean_tree(((t_operator *)head)->left);
			clean_tree(((t_operator *)head)->right);
			clean_operator((t_operator *)head);
		}
		else if (node_type == COMMAND)
		{
			clean_command((t_command *)head);
		}
	}
}
