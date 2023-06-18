/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:21:16 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/18 20:03:47 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

pid_t	exec_cmd(t_node *node)
{
	t_cmd	*cmd;

	cmd = (t_cmd *) node;
	cmd->pid = fork();
	if (cmd->pid < 0)
		perror("Error creating child process ...\n");
	if (cmd->pid == 0)
	{
		printf("EXEC_CMD| => %s\n", cmd->name);
		exit(0);
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
		if (node->type == CMD)
			return (waitpid(exec_cmd(node), &status, 0), WEXITSTATUS(status));
		if (((t_operator *)node)->left->type == CMD)
			pid = exec_cmd(((t_operator *)node)->left);
		else if (((t_operator *) node)->left->type == SUBSHELL)
			pid = exec_subshell(((t_operator *)node)->left);
		else
			exec_cmds(((t_operator *)node)->left);
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
	return (status);
}
