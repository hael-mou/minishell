/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:44:04 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/29 08:29:45 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

/*###############################################################
#		* LEXER :												#
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

typedef struct s_token
{
	char	*name;
	t_state	type;
}	t_token;

/*###############################################################
#		* env :												#
###############################################################*/
typedef struct s_var
{
	char		*key;
	char		*value;
}	t_var;


#endif