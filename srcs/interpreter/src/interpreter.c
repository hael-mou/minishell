/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:21:16 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/10 22:51:25 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

int	interpreter(t_node *tree)
{
	int	status;

	if (!tree)
		return (0);
	status = exec_branch(tree);
	return (status);
}

pid_t	exec_cmd(t_command *cmd, int position, int p_type)
{
	int	fd[2];
	int	*in_out;

	pipe(fd);
	extract_command((t_node *) cmd);
	if (exec_builtins(cmd, FIRST_PART) == SUCCESS)
		return (0);
	in_out = get_command_inout(cmd->in_out);
	cmd->pid = fork();
	if (cmd->pid < 0)
		perror("Error creating child process ...\n");
	if (cmd->pid == 0)
	{
		dup_process_inout(fd, in_out, position, p_type);
		close_all_fd(cmd->in_out, fd);
		if (exec_builtins(cmd, SECOND_PART) == SUCCESS)
			exit(EXIT_SUCCESS);
		if (execve(cmd->path, cmd->args, get_env(g_sys.env)) == -1)
			exit(printf("Error of Command\n"));
	}
	if (p_type == PIPE)
	{
		close(g_sys.pipeline);
		g_sys.pipeline = dup(fd[0]);
	}
	close_all_fd(cmd->in_out, fd);
	free(in_out);
	return (cmd->pid);
}

int	exec_branch(t_node *node)
{
	int			status;
	pid_t		pid;

	status = 0;
	if (!node)
		return (0);
	while (node)
	{
		if (node->type == COMMAND)
			pid = exec_cmd((t_command *) node, RIGHT, COMMAND);
		else if (node->type == SUBSHELL
			|| ((t_operator *) node)->left->type == SUBSHELL)
			pid = exec_subshell(((t_operator *)node)->left);
		else if (((t_operator *)node)->left->type != COMMAND)
			pid = exec_branch(((t_operator *)node)->left);
		else
			pid = exec_cmd((t_command *)((t_operator *) node)->left, LEFT, node->type);
		if (node->type != PIPE)
			waitpid(pid, &status, 0);
		if (node->type == COMMAND || (status != 0 && node->type == AND)
				|| (status == 0 && node->type == OR))
			break ;
		node = ((t_operator *) node)->right;
	}

	return (WEXITSTATUS(status));
}

//=== exec_subshell ============================================================
int	exec_subshell(t_node *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		perror("Error creating child process ...\n");
	if (pid == 0)
		exit(exec_branch(node));
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

//=== exec_builtins ===========================================================
int	exec_builtins(t_command *cmd, int start)
{
	int		index;

	if (ft_strcmp(cmd->name, "clear") == 0)
		return (clear(), 0);
	index = start;
	while (++index < 7)
	{
		if (ft_strcmp(cmd->name, g_sys.builtins.name[index]) == 0)
			return ((g_sys.builtins.func[index])(cmd->args));
	}
	return (FAILURE);
}
/*
pid_t	extract_exit_status(t_node *tree)
{
	pid_t	pid;
	int		status;

	while (tree)
	{
		if (tree->type == COMMAND)
		{
	//		printf("PID|%s| => %d\n", ((t_command *)tree)->name, ((t_command *)tree)->pid);
			waitpid(((t_command *)tree)->pid, &status, 0);
			pid = WEXITSTATUS(status);
			break ;
		}
		else if (((t_operator *)tree)->left->type == COMMAND)
		{
	//		printf("PID|%s| => %d\n", ((t_command *)((t_operator *)tree)->left)->name, ((t_command *)((t_operator *)tree)->left)->pid);
			waitpid(((t_command *)((t_operator *)tree)->left)->pid, &status, 0);
			pid = WEXITSTATUS(status);
		}
		else
			extract_exit_status(((t_operator *)tree)->left);
		tree = ((t_operator *)tree)->right;
	}
	return (status);
}*/
