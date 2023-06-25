/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:23:32 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/25 04:30:58 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//=== parse_seq =========================================================
t_node	*parser(t_list *tokens)
{
	t_node	*tree;
	void	*copy;

	copy = tokens;
	tree = parse_seq(&tokens);
	clean_tokenizer(copy);
	return (tree);
}
