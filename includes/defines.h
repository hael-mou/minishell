/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:17:12 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/18 16:29:56 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*###############################################################
#		* STANDART FD  :										#
###############################################################*/
# define STD_IN		        0
# define STD_OUT	        1
# define STD_ERROR	        2

/*###############################################################
#		* EXIT STATUS  :										#
###############################################################*/
//# define EXIT_FAILURE		1
//# define EXIT_SUCCESS		0
# define PERMISSION_DINED	126
# define CMD_NOT_FOUND		127

/*###############################################################
#		* RETURN  :												#
###############################################################*/
# define FAILURE			0
# define SUCCESS			1
# define TRUE		        1
# define FALSE		        0
# define ERROR  	        -1

/*###############################################################
#		* Token type :		    							 	#
###############################################################*/
# define OTHER				0
# define START				0
# define PIPE				1
# define REDIR_OUT			2
# define REDIR_IN			3
# define SINGLE_QUOTES		4
# define DOUBLE_QUOTES		5
# define STRING				6
# define HERE_DOC			7
# define REDIR_APPEND		8
# define SEMICOLON			9
# define AND				10
# define OR					11
# define OPEN_PARENTHESIS	12
# define CLOSE_PARENTHESIS	13
# define END				14
# define COMMAND			15
# define SUBSHELL			16
# define OPERATOR			17
# define REDIR				18

#endif /* DEFINES_H */
