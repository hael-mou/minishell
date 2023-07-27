/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:21:16 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/27 21:44:37 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

//=== interpreter ==============================================================
int	interpreter(t_node *root)
{
	g_sys.area = INTERPRETER;
	if (root == NULL || g_sys.merrno != -1)
	{
		if (g_sys.merrno != -1)
			g_sys.exit_status = (g_sys.merrno != -1);
		g_sys.merrno = -1;
		return (0);
	}
	exec_branches(root);
	g_sys.exit_status = extract_exit_status(root, FALSE);
	return (SUCCESS);
}

//=== exec_branches ============================================================
pid_t	exec_branches(t_node *node)
{
	int			status;
	pid_t		pid;

	while (node)
	{
		create_pipe(&g_sys.pipeline, (node->type == PIPE));
		if (node->type == COMMAND)
			pid = exec_cmd(node);
		else if (node->type == SUBSHELL)
			pid = exec_subshell(node);
		else if (get_left_node(node)->type == COMMAND)
			pid = exec_cmd(get_left_node(node));
		else if (get_left_node(node)->type == SUBSHELL)
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
	node->pid = fork();
	if (node->pid < 0)
		perror("Error creating child process ...\n");
	if (node->pid == 0)
	{
		if (g_sys.pipeline.fd[1] > -1)
			dup2(g_sys.pipeline.fd[1], 1);
		close_pipe(g_sys.pipeline.fd);
		exec_branches(get_left_node(node));
		close(g_sys.pipeline.offset);
		exit(extract_exit_status(get_left_node(node), FALSE));
	}
	return (node->pid);
}

//=== exec_builtins ============================================================
int	exec_builtins(t_node *cmd, int *in_out)
{
	int	index;
	int	status;

	index = -1;
	while (++index < 8)
	{
		if (ft_strcmp(get_cmd_name(cmd), g_sys.builtins.name[index]) == 0)
		{
			g_sys.merrno = -1;
			if (in_out)
			{
				dup2(in_out[0], 0);
				dup2(in_out[1], 1);
			}
			status = g_sys.builtins.func[index](get_cmd_args(cmd));
			if (in_out)
			{
				dup2(g_sys.std_in, 0);
				dup2(g_sys.std_out, 1);
			}
			return (status);
		}
	}
	return (ERROR);
}

//=== extract_exit_status ======================================================
pid_t	extract_exit_status(t_node *node, int sig)
{
	int		status;

	while (node)
	{
		if (node->type == COMMAND || node->type == SUBSHELL)
			waitpid(node->pid, &status, 0);
		else if (get_left_node(node)->type == COMMAND
			|| get_left_node(node)->type == SUBSHELL)
			waitpid(get_left_node(node)->pid, &status, 0);
		else
			extract_exit_status(get_left_node(node), sig);
		if (WIFSIGNALED(status) == 1)
			sig = TRUE;
		if (node->type == COMMAND)
			break ;
		node = get_right_node(node);
	}
	if (sig == TRUE)
		return (130);
	return ((((*(int *)&(status)) >> 8) & 0x000000ff));
}
