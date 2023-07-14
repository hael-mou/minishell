/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:21:16 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/14 21:44:37 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

//=== interpreter ==============================================================
int	interpreter(t_node *root)
{
	int	status;

	if (!root)
		return (0);
	if (root->type == COMMAND)
	{
		extract_command(root);
		if (exec_builtins((t_command *) root) == SUCCESS)
			return (EXIT_SUCCESS);
	}
	status = exec_branch(root);
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
		create_pipe(g_sys.pipeline.fd, (node->type == PIPE));
		if (node->type == COMMAND)
			pid = exec_cmd((t_command *) node);
		else if (((t_operator *)node)->left->type == COMMAND)
			pid = exec_cmd((t_command *)((t_operator *) node)->left);
		else if (node->type == SUBSHELL || ((t_operator *)node)->left->type == SUBSHELL)
			pid = exec_subshell(((t_operator *)node)->left);
		else
			pid = exec_branch(((t_operator *)node)->left);
		if (node->type != PIPE)
			waitpid(pid, &status, 0);
		if (node->type == COMMAND || (status != 0 && node->type == AND)
				|| (status == 0 && node->type == OR))
			break ;
		update_pipeline(&g_sys.pipeline, (node->type == PIPE));
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
	{
		if (g_sys.pipeline.fd[1] > -1)
			dup2(g_sys.pipeline.fd[1], 1);
		exit(exec_branch(node));
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
