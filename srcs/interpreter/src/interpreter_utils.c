/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:16:20 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/23 23:54:03 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

//=== get_env ==================================================================
char	**get_env(t_list *g_env)
{
	char	**env;
	int		index;

	index = 0;
	env = malloc(sizeof(char *) * (ft_lstsize(g_env) + 1));
	if (!env)
		return (NULL);
	while (g_env)
	{
		env[index] = ft_strdup(get_var_name(g_env));
		env[index] = ft_vstrjoin(3, env[index], "=", get_var_value(g_env));
		index++;
		g_env = g_env->next;
	}
	env[index] = NULL;
	return (env);
}

//=== whereis_command ==========================================================
char	*whereis_cmd(char *cmd)
{
	char	*cmd_path;
	char	*path;
	int		pathlen;

	if (!cmd)
		return (NULL);
	path = search_var(g_sys.env, "PATH");
	if (ft_strncmp(cmd, "./", 2) == 0 || *cmd == '/')
	{
		if (access(cmd, F_OK) == -1)
			g_sys.merrno = 6;
		else if (access(cmd, X_OK) == -1)
			g_sys.merrno = 5;
		return (ft_strdup(cmd));
	}
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
	g_sys.merrno = 1;
	return (NULL);
}

//=== close_inout ==============================================================
int	close_inout(t_list *file)
{
	while (file)
	{
		close(get_file_fd(file));
		file = file->next;
	}
	return (SUCCESS);
}

//=== my_execve ================================================================
int	my_execve(t_node *cmd)
{
	if (exec_builtins(cmd, NULL) == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	if (g_sys.merrno == -1)
 		execve(get_cmd_path(cmd), get_cmd_args(cmd), get_env(g_sys.env));
	return (ERROR);
}

//=== get_mode =================================================================
int	get_mode(int type)
{
	if (type == REDIR_IN)
		return (O_RDONLY);
	if (type == REDIR_APPEND)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (O_CREAT | O_WRONLY | O_TRUNC);
}

//=== print_error_msg ==========================================================
int	print_error_msg(t_node *cmd)
{
	t_list	*file;
	char	*tmp;
	
	if (g_sys.merrno == 1 || g_sys.merrno == 5 || g_sys.merrno == 6)
		tmp = get_cmd_name(cmd);
	if (g_sys.merrno == 3 || g_sys.merrno == 4)
	{
		file = get_cmd_iofile(cmd);
		while (file && get_file_fd(file) > -1)
			file = file->next;
		tmp = get_file_name(file);
	}
	printf("TMP| ====> %s\n", tmp);
	return (0);
}
