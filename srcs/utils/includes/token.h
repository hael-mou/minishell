/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:15:26 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/18 08:55:38 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/*###############################################################
#		* Includes :		    							 	#
###############################################################*/
# include "libft.h"
# include "defines.h"

/*###############################################################
#		* token Types :		    							 	#
###############################################################*/
typedef struct s_token
{
	char	*name;
	int		type;
}	t_token;

/*###############################################################
#		* Functions :		    							 	#
###############################################################*/
t_token		*create_token(char *start, char *end, int type);
void		free_token(void *content);
t_list		*listadd_token(t_list **list, t_token *new_token);
char		*get_token_name(t_list *token);
int			get_token_type(t_list *token);

#endif /* TOKEN_H */