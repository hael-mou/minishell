/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:30:18 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/24 17:48:24 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*#############################################################################
#		* Includes : 	    												  #
#############################################################################*/
# include "libft.h"
# include "analyzer.h"
# include "tokenizer.h"

/*#############################################################################
#		* Functions : 	    												  #
#############################################################################*/
// lexer Function :
t_list		*lexer(char *cmd_line);

// lexer utils :
t_list		*tokenizer(char *line);
t_list		*analyzer(t_list *tokens);

#endif
