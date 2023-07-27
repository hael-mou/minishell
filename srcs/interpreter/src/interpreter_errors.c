/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:49:13 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/26 23:19:28 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

//=== print_error_msg ==========================================================
int	print_error_msg(t_node *cmd)
{
	t_list	*file;
	char	*name;
	char	*msg;
	int		exit;

	if (g_sys.merrno == -1)
		return (0);
	if (g_sys.merrno == 1 || g_sys.merrno == 2 || g_sys.merrno == 6)
		name = get_cmd_name(cmd);
	if ((g_sys.merrno >= 3 && g_sys.merrno <= 5) || g_sys.merrno == 7)
	{
		file = get_cmd_iofile(cmd);
		while (file && get_file_fd(file) > -1)
			file = file->next;
		name = get_file_name(file);
	}
	msg = PERMISSION_DENIED;
	if (g_sys.merrno == 1)
		msg = CMD_NOT_FOUND;
	if (g_sys.merrno >= 2 && g_sys.merrno <= 3)
		msg = NO_SUCH_FILE;
	if (g_sys.merrno == 7)
		msg = AMBIGUOUS_REDIRECT;
	exit = 127 - 126 * ((g_sys.merrno >= 3 && g_sys.merrno <= 5) || g_sys.merrno == 7);
	exit -= (g_sys.merrno == 6);
	return (ft_print_error("minishell: %\n", msg), exit);
}
