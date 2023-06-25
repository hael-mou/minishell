/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:21:16 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/21 22:51:28 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

int	interpreter(t_node *tree)
{
	int	status;

	status = exec_cmds(tree);
	return (status);
}

pid_t	exec_cmd(t_node *node)
{
	t_command	*cmd;

	cmd = (t_command *) node;
	cmd->pid = fork();
	if (cmd->pid < 0)
		perror("Error creating child process ...\n");
	if (cmd->pid == 0)
	{
		printf("EXEC_COMMAND| => %s\n", cmd->name);
//		if (execve(cmd->path, cmd->args, get_env(g_env)) == -1)
//			exit(printf("Error of Command\n"));
		exit(1);
	}
	return (cmd->pid);
}

int	exec_cmds(t_node *node)
{
	int			status;
	pid_t		pid;

	status = 0;
	if (!node)
		return (-1);
	while (node)
	{
		if (node->type == COMMAND)
			return (waitpid(exec_cmd(node), &status, 0), WEXITSTATUS(status));
		if (((t_operator *)node)->left->type == COMMAND)
			pid = exec_cmd(((t_operator *)node)->left);
		else if (((t_operator *) node)->left->type == SUBSHELL)
			pid = exec_subshell(((t_operator *)node)->left);
		else
			pid = exec_cmds(((t_operator *)node)->left);
		if (node->type != PIPE)
		{
			waitpid(pid, &status, 0);
			status = WEXITSTATUS(status);
		}
		if ((status != 0 && node->type == AND)
				|| (status == 0 && node->type == OR))
			break ;
		node = ((t_operator *) node)->right;
	}
	return (status);
}

int	exec_subshell(t_node *node)
{
	pid_t	pid;
	int		status;

	status = -1;
	pid = fork();
	if (pid < 0)
		perror("Error creating child process ...\n");
	if (pid == 0)
	{
		status = exec_cmds(node);
		exit(status);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
