/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:23:48 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/18 15:21:52 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*###############################################################
#		* Includes :		    							 	#
###############################################################*/
# include "defines.h"
# include "libft.h"
# include "file.h"
# include "operator.h"
# include "command.h"
# include "node.h"
# include "token.h"

/*###############################################################
#  	   * Functions :											#
###############################################################*/
// Parser :
t_node		*parser(t_list *tokens);

// Parse tree:
t_node		*parse_seq(t_list **tokens);
t_node		*parse_and_or(t_list **tokens);
t_node		*parse_pipe(t_list **tokens);
t_node		*parse_command(t_list **tokens);
t_node		*parse_subshell(t_list **tokens);

// parser utils :
int			is_redirection(t_list *token);

#endif
