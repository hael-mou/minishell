/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 07:37:55 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/24 09:33:39 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*###############################################################
#  	   * Includes :		    								 	#
###############################################################*/
# include "libft.h"

/*###############################################################
#  	   * struct     :		    								#
###############################################################*/
typedef enum e_state
{
	start,
	redir,
	redir2,
	pipes,
	string,
	quotes,
	end,
}	t_state;

// define :
typedef t_state	(*t_state_func)(char, t_state);

/*###############################################################
#  	   * Functions :											#
###############################################################*/
// minishell toknizer
t_list		*tokenizer(char *line);

// utils :
t_state		get_next_state(t_state state, char input);
void		create_token(t_list **list, char *start, char *end, t_state type);
void		print_tokens(t_list *list);

// function state
t_state		st_start(char input, t_state prv_state);
t_state		st_string(char input, t_state prv_state);
t_state		st_redir(char input, t_state prv_state);
t_state		st_pipes(char input, t_state prv_state);

#endif /* LEXER_H */
