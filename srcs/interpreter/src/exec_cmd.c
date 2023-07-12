/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:50:04 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/12 22:55:06 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "interpreter.h"

//=== exec_cmd ================================================================
pid_t	exec_cmd(t_command *cmd, int permission)
{
	int	fd[2];

//	printf("P_TYPE| => %d\nROOT| => %d\n", p_type, root);
	pipe(fd);
//	permission = (position == LEFT) && p_type == PIPE;
	extract_command((t_node *) cmd);
	if (exec_builtins(cmd, FIRST_PART) == SUCCESS)
		return (0);
	cmd->pid = fork();
	if (cmd->pid < 0)
		perror("Error creating child process ...\n");
	if (cmd->pid == 0)
	{
		dup_process_inout(fd, get_command_inout(cmd->in_out), permission);
		close_all_fd(cmd->in_out, fd);
		if (exec_builtins(cmd, SECOND_PART) == SUCCESS)
			exit(EXIT_SUCCESS);
		if (execve(cmd->path, cmd->args, get_env(g_sys.env)) == -1)
			exit(print_error_msg(cmd));
	}
	update_pipeline(fd, permission);
	close_all_fd(NULL, fd);
	return (cmd->pid);
}

//=== extract_command =========================================================
void	extract_command(t_node *cmd)
{
	char	**args;
	char	*tmp;

	tmp = get_cmd_name(cmd);
	//args = expand_arg(tmp); expand not works 
	args = ft_split(tmp, '\5');
	if (args != NULL)
	{
		set_cmd_args(cmd, args);
		set_cmd_name(cmd, *args);
		set_cmd_path(cmd, whereis_cmd(*args));
	}
	free(tmp);
}

//=== get_command_inout =======================================================
int	*get_command_inout(t_list *file)
{
	int	*in_out;
	int	mode;
	int	fd;

	in_out = (int *) malloc(sizeof(int) * 2);
	ft_memset(in_out, 255, 8);
	while (in_out && file)
	{
		mode = GET_MODE(get_file_type(file));
		if (get_file_type(file) == REDIR_IN)
			fd = open(get_file_name(file), O_RDONLY);
		if (get_file_type(file) == REDIR_OUT || get_file_type(file) == REDIR_APPEND)
			fd = open(get_file_name(file), mode, 0644);
		if (fd < 0)
			exit(1);
		set_file_fd(file, fd);
		if (get_file_type(file) == REDIR_IN && get_file_type(file->next) != REDIR_IN)
			in_out[0] = get_file_fd(file);
		// NEED TO USE ONE CONDITION FOR THESE TWO
		if ((get_file_type(file) == REDIR_OUT && get_file_type(file->next) != REDIR_OUT))
			in_out[1] = get_file_fd(file);
//		if (get_file_type(file) == REDIR_APPEND && get_file_type(file->next) != REDIR_APPEND)
//			in_out[1] = get_file_fd(file);
		// CASE OF HEREDOC
		file = file->next;
	}
	return (in_out);
}

//=== dup_process_inout =======================================================
int	dup_process_inout(int *fd, int *in_out, int permission)
{
//	printf("PERMISSION| => %d\n", permission);
	if (!in_out)
		exit(127);
	if (g_sys.pipeline > -1 && in_out[0] == -1)
		dup2(g_sys.pipeline, 0);
	if (in_out[0] > -1)
		dup2(in_out[0], 0);
	if (permission)
		dup2(fd[1], 1);
	if (in_out[1] > -1)
		dup2(in_out[1], 1);
	free(in_out);
	return (SUCCESS);
}

//=== update_pipeline =========================================================
void	update_pipeline(int *fd, int permission)
{
	if (permission)
	{
	//	printf(">>>>>>> UPDATED ...\n");
		close(g_sys.pipeline);
		g_sys.pipeline = dup(fd[0]);
	}
}
