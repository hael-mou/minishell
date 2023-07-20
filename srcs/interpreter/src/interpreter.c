/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:21:16 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/20 15:43:34 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

//=== interpreter ==============================================================
int	interpreter(t_node *root)
{
	if (!root)
		return (0);
	if (root->type == COMMAND)
		return (exec_simple_cmd(root));
	exec_branches(root);
	extract_exit_status(root);
	return (SUCCESS);
}

//=== exec_branches ============================================================
pid_t	exec_branches(t_node *node)
{
	int			status;
	pid_t		pid;

	status = 0;
	while (node)
	{
		create_pipe(&g_sys.pipeline, (node->type == PIPE));
		if (node->type == COMMAND)
			pid = exec_cmd(node);
		else if (get_left_node(node)->type == COMMAND)
			pid = exec_cmd(get_left_node(node));
		else if (node->type == SUBSHELL
			|| get_left_node(node)->type == SUBSHELL)
			pid = exec_subshell(get_left_node(node));
		else
			pid = exec_branches(get_left_node(node));
		if (node->type == AND || node->type == OR)
			waitpid(pid, &status, 0);
		if (node->type == COMMAND || (status != 0 && node->type == AND)
			|| (status == 0 && node->type == OR))
			break ;
		update_pipeline(&g_sys.pipeline);
		node = get_right_node(node);
	}
	return (pid);
}

//=== exec_subshell ============================================================
pid_t	exec_subshell(t_node *node)
{
	pid_t	pid;

	if (node->type == SUBSHELL)
		node = get_left_node(node);
	pid = fork();
	if (pid < 0)
		perror("Error creating child process ...\n");
	if (pid == 0)
	{
		if (g_sys.pipeline.fd[1] > -1)
			dup2(g_sys.pipeline.fd[1], 1);
		close_pipe(g_sys.pipeline.fd);
		exec_branches(node);
		close(g_sys.pipeline.offset);
		exit(extract_exit_status(node));
	}
	return (pid);
}

//=== exec_builtins ============================================================
int	exec_builtins(t_node *cmd)
{
	int	index;

	index = -1;
	while (++index < 8)
	{
		if (ft_strcmp(get_cmd_name(cmd), g_sys.builtins.name[index]) == 0)
			return ((g_sys.builtins.func[index])(get_cmd_args(cmd)));
	}
	return (FAILURE);
}

//=== extract_exit_status ======================================================
pid_t	extract_exit_status(t_node *node)
{
	int		status;

	while (node)
	{
		if (node->type == COMMAND)
		{
			waitpid(get_cmd_pid(node), &status, 0);
			break ;
		}
		else if (get_left_node(node)->type == COMMAND)
			waitpid(get_cmd_pid(get_left_node(node)), &status, 0);
		else
			extract_exit_status(get_left_node(node));
		node = get_right_node(node);
	}
	return (WEXITSTATUS(status));
}
