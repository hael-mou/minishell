/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 08:40:52 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/25 13:07:59 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

//=== extract command ====================================================
void	extract_command(t_node *cmd)
{
	char	**args;
	char	*tmp;
	
	tmp = get_cmd_name(cmd);
	//args = expand_arg(tmp); expand not works 
	args = ft_split(tmp, '\5');
	if (args != NULL)
	{
		set_cmd_args(cmd, args);
		set_cmd_name(cmd, *(args));
		set_cmd_path(cmd, whereis_cmd(*(args)));
	}
	free(tmp);
}

//=== whereis_command ====================================================
char	*whereis_cmd(char *cmd)
{
	char	*cmd_path;
	char	*path;
	int		pathlen;

	path = search_var(g_sys.env, "PATH");
	if (ft_strncmp(cmd, "./", 2) == 0 || *cmd == '/')
		return (ft_strdup(cmd));
	while (cmd && path && *path)
	{
		pathlen = ft_toklen(path, ':');
		cmd_path = ft_strnjoin(ft_strdup(cmd), path, pathlen);
		if (access(cmd_path, F_OK) == F_OK)
			return (cmd_path);
		free(cmd_path);
		while (path[pathlen] == ':')
			pathlen++;
		path += pathlen;
	}
	return (NULL);
}
