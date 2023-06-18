/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:07:00 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/18 12:20:54 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

//=== create_command_node ===============================================
t_command	*create_command_node(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	cmd->type = COMMAND;
	return (cmd);
}
