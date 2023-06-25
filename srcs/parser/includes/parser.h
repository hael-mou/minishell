/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:23:48 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/25 03:08:37 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*###############################################################
#		* Includes :		    							 	#
###############################################################*/
# include "tokenizer.h"
# include "defines.h"
# include "types.h"

# include "operator.h"
# include "command.h"
# include "file.h"

/*###############################################################
#  	   * Functions :											#
###############################################################*/
// Parser :
t_node		*parser(t_list *tokens);
void		clean_tree(t_node *tree);

// Parse tree:
t_node		*parse_seq(t_list **tokens);
t_node		*parse_and_or(t_list **tokens);
t_node		*parse_pipe(t_list **tokens);
t_node		*parse_command(t_list **tokens);
t_node		*parse_subshell(t_list **tokens);

//parse command utils:
t_list		*extract_files(t_list *tokens);
char		*join_argument(t_list *tokens);
int			is_end_of_command(t_list *token);
int			is_redirection(t_list *token);

#endif
