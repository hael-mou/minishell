/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:21:16 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/09 18:08:29 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

pid_t	extract_exit_status(t_node *tree);

int	interpreter(t_node *tree)
{
	int	status;

	if (!tree)
		return (0);
	status = exec_cmds(tree);
	return (status);
}

// read from pipe only in case of pipe or subshell
pid_t	exec_cmd(t_command *cmd, int position, int p_type)
{
	int	fd[2];
	int	*in_out;

	manage_pipe(fd, CREAT);
	extract_command((t_node *) cmd);
	in_out = get_command_inout(cmd->in_out);
	if (cmd->pid < 0)
		perror("Error creating child process ...\n");
	if (cmd->pid == 0)
	{
		if (g_sys.pipeline > -1)
			dup2(g_sys.pipeline, 0);
		if (in_out[0] > -1)
			dup2(in_out[0], 0);
		if (position == LEFT && p_type == PIPE)
			dup2(fd[1], 1);
		if (in_out[1] > -1)
			dup2(in_out[1], 1);
//		if (!ft_strcmp(cmd->name, "env") || !ft_strcmp(cmd->name, "echo"))
//			exit(minishell_echo(cmd->args));
		manage_pipe(fd, CLOSE);
		if (execve(cmd->path, cmd->args, get_env(g_sys.env)) == -1)
			exit(printf("Error of Command\n"));
	}
	if (p_type == PIPE)
		g_sys.pipeline = dup(fd[0]);
	manage_pipe(fd, CLOSE);
	return (cmd->pid);
}

int	exec_cmds(t_node *node)
{
	int			status;
	pid_t		pid;

	status = 0;
	if (node == NULL)
		return (0);
	while (node)
	{
		if (node->type == COMMAND)
			pid = exec_cmd((t_command *) node, RIGHT, COMMAND);
		else if (((t_operator *)node)->left->type == COMMAND)
			pid = exec_cmd((t_command *)((t_operator *) node)->left, LEFT, node->type);
		else if (((t_operator *) node)->left->type == SUBSHELL)
			pid = exec_subshell(((t_operator *)node)->left);
		else
			pid = exec_cmds(((t_operator *)node)->left);
		if (node->type != PIPE)
			waitpid(pid, &status, 0);
		if ((status != 0 && node->type == AND)
			|| (status == 0 && node->type == OR) || node->type == COMMAND)
			break ;
		node = ((t_operator *) node)->right;
	}
	return (WEXITSTATUS(status));
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

int	exec_builtins(t_node *node)
{
	t_command	*cmd;
	int			re;

	cmd = (t_command *) node;
	if (!ft_strcmp(cmd->name, "cd"))
		re = minishell_cd(cmd->args);
	if (!ft_strcmp(cmd->name, "exit"))
		re = minishell_exit(cmd->args);
	if (!ft_strcmp(cmd->name, "set"))
		re = minishell_export(cmd->args);
	if (!ft_strcmp(cmd->name, "unset"))
		re = minishell_unset(cmd->args);
	if (!ft_strcmp(cmd->name, "clear"))
		clear();
	return (re);
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
