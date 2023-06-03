/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:44:04 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/03 17:32:17 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

/*###############################################################
#		* LEXER :												#
###############################################################*/
// state :
# define	OTHER				0
# define	START				0
# define	PIPE				1
# define	REDIR_OUT			2
# define	REDIR_IN			3
# define	SINGLE_QUOTES		4
# define	DOUBLE_QUOTES		5
# define	STRING				6
# define	HERE_DOC			7
# define	REDIR_APPEND		8
# define	SEMICOLON			9
# define	AND					10
# define	OR					11
# define	OPEN_PARENTHESIS	12
# define	CLOSE_PARENTHESIS	13
# define	END					14

typedef struct s_token
{
	char	*name;
	int		type;
}	t_token;

/*###############################################################
#		* env :													#
###############################################################*/
typedef struct s_var
{
	char		*key;
	char		*value;
}	t_var;


#endif