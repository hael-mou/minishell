/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:16:20 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/12 11:26:10 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

//=== get_env =================================================================
char	**get_env(t_list *g_env)
{
	char	**env;
	int		i;

	env = malloc(sizeof(char *) * (ft_lstsize(g_env) + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (g_env)
	{
		env[i++] = ft_strdup((char *) g_env->content);
		g_env = g_env->next;
	}
	env[i] = NULL;
	return (env);
}

//=== whereis_command =========================================================
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
		cmd_path = ft_substr(path, 0, pathlen);
		cmd_path = ft_strjoin(cmd_path, ft_strjoin(ft_strdup("/"), ft_strdup(cmd)));
		if (access(cmd_path, F_OK) == F_OK)
			return (cmd_path);
		free(cmd_path);
		while (path[pathlen] == ':')
			pathlen++;
		path += pathlen;
	}
	return (NULL);
}

//=== close_all_fd ============================================================
int	close_all_fd(t_list *file, int *fd)
{
	while (file)
	{
		close(get_file_fd(file));
		file = file->next;
	}
	close(fd[0]);
	close(fd[1]);
	return (SUCCESS);
}

//=== print_error_msg =========================================================
int	print_error_msg(t_command *cmd)
{
	if (cmd->path == NULL)
		return (ft_print_error(CMD_NOT_FOUND":%s\n",  cmd->name), 127);
	return (0);
}
