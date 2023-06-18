/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:02:40 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/18 12:06:05 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"

//=== create_operator_node ==============================================
t_node	*create_operator_node(t_node *left, t_node *right, int type)
{
	t_operator	*operator;

	operator = ft_calloc(1, sizeof(t_operator));
	if (operator == NULL)
		return (NULL);
	operator->type = type;
	operator->left = left;
	operator->right = right;
	return ((t_node *) operator);
}

//=== get_left_node =====================================================
t_node	*get_left_node(t_operator *node)
{
	if (node != NULL)
		return (node->left);
	return (NULL);
}

//=== get_right_node ====================================================
t_node	*get_right_node(t_operator *node)
{
	if (node != NULL)
		return (node->right);
	return (NULL);
}
