/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:39:52 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/19 12:25:23 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_H
# define OPERATOR_H

/*###############################################################
#		* Includes :		    							 	#
###############################################################*/
# include "libft.h"
# include "defines.h"
# include "types.h"

/*###############################################################
#		* operator Types :		    						 	#
###############################################################*/
typedef struct s_operator
{
	int			type;
	t_node		*right;
	t_node		*left;
}				t_operator;

/*###############################################################
#		* Functions :		    							 	#
###############################################################*/
int		get_node_type(void *node);
t_node	*create_operator_node(t_node *left, t_node *right, int type);
void	clean_operator(t_operator *node);
t_node	*get_left_node(t_operator *node);
t_node	*get_right_node(t_operator *node);

#endif /* OPERATOR_H */
