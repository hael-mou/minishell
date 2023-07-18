/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:21:16 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/18 23:54:06 by oezzaou          ###   ########.fr       */
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
	exec_branch(root);
	// EXIT STATUS IS NOT COMPLETE AND IT NEEDS MORE WORK (SUBSHELL CASE)
	g_sys.exit_status = extract_exit_status(root);
	return (SUCCESS);
}

//=== exec_simple_cmd ==========================================================
int	exec_simple_cmd(t_node *cmd)
{
	int	status;
	int	pid;

	status = 0;
	if (get_cmd_iofile(cmd) == NULL)
	{
		extract_command(cmd);
		if (exec_builtins((t_command *) cmd) == SUCCESS)
			return (status);
	}
	pid = exec_cmd((t_command *) cmd);
	waitpid(pid, &status, 0);
	return (status);
}

//=== exec_branch ==============================================================
int	exec_branch(t_node *node)
{
	int			status;
	pid_t		pid;

	status = 0;
	while (node)
	{
		create_pipe(&g_sys.pipeline, (node->type == PIPE));
		if (node->type == COMMAND)
			pid = exec_cmd((t_command *) node);
		else if (((t_operator *)node)->left->type == COMMAND)
			pid = exec_cmd((t_command *) get_left_node((t_operator *) node));
		else if (node->type == SUBSHELL || ((t_operator *) node)->left->type == SUBSHELL)
			pid = exec_subshell(get_left_node((t_operator *) node));
		else
			pid = exec_branch(get_left_node((t_operator *) node));
		if (node->type != PIPE && node->type != COMMAND)
			waitpid(pid, &status, 0);
		if (node->type == COMMAND || (status != 0 && node->type == AND)
				|| (status == 0 && node->type == OR))
			break ;
		update_pipeline(&g_sys.pipeline, (node->type == PIPE));
		node = get_right_node((t_operator *) node);
	}
	return (WEXITSTATUS(status));
}

//=== exec_subshell ============================================================
int	exec_subshell(t_node *node)
{
	pid_t	pid;
	int		status;

	if (node->type == SUBSHELL)
		node = get_left_node((t_operator *) node);
	pid = fork();
	if (pid < 0)
		perror("Error creating child process ...\n");
	if (pid == 0)
	{
		if (g_sys.pipeline.fd[1] > -1)
			dup2(g_sys.pipeline.fd[1], 1);
		exec_branch(node);
		exit(extract_exit_status(node));
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

//=== exec_builtins ============================================================
int	exec_builtins(t_command *cmd)
{
	int	index;

	index = -1;
	while (++index < 8)
	{
		if (ft_strcmp(cmd->name, g_sys.builtins.name[index]) == 0)
			return ((g_sys.builtins.func[index])(cmd->args));
	}
	return (FAILURE);
}

//=== extract_exit_status ======================================================
pid_t	extract_exit_status(t_node *node)
{
	pid_t	pid;
	int		status;

	while (node)
	{
		if (node->type == COMMAND)
		{
			waitpid(get_cmd_pid(node), &status, 0);
			pid = WEXITSTATUS(status);
			break ;
		}
		else if (get_left_node((t_operator *) node)->type == COMMAND)
		{
			waitpid(((t_command *)((t_operator *)node)->left)->pid, &status, 0);
			pid = WEXITSTATUS(status);
		}
		else
			extract_exit_status(((t_operator *)node)->left);
		node = ((t_operator *) node)->right;
	}
	return (status);
}
