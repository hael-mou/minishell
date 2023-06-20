/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:21:16 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/19 23:23:49 by oezzaou          ###   ########.fr       */
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
	return (status);
}

int	get_in_out(t_list *in_out)
{
	t_list	*cursor;
	int		type;

	cursor = in_out;
	while (cursor)
	{
		type = get_file_type(cursor);
		if (type == REDIR_IN)
		{
			(cursor->fd)[0] = open(get_file_name(cursor), O_RDONLY);
			if ((cursor->fd)[0] == -1)
				return (ERROR);
		}
		if (type == REDIR_OUT || type == REDIR_APPEND)
		{
			(cursor->fd)[1] = open(get_file_name(cursor), O_CREAT | O_WRONLY, 0666);
			if ((cursor->fd)[1])
				return (ERROR);
		}
		cursor = cursor->next;
	}
	return (ERROR);
}
