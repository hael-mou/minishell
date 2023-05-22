/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 07:37:55 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/22 09:08:29 by hael-mou         ###   ########.fr       */
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
	pipes,
	redir,
	redir2,
	string,
	quotes,
	end,
}	t_state;

/*###############################################################
#  	   * Functions :											#
###############################################################*/
// minishell toknizer
t_list		*tokenizer(char *line);
// function state
t_state		st_start(char input);
t_state		st_string(char input, t_state prv_state);
t_state		st_redir(char input, t_state prv_state);

#endif /* LEXER_H */