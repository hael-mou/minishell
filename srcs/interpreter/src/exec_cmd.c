/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:50:04 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/16 21:22:27 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "interpreter.h"

//=== exec_cmd =================================================================
pid_t	exec_cmd(t_command *cmd)
{
	int	*in_out;

	extract_command((t_node *) cmd);
	cmd->pid = fork();
	if (cmd->pid < 0)
		perror("Error creating child process ...\n");
	if (cmd->pid == 0)
	{
		in_out = get_command_inout(cmd->in_out);
		dup_process_inout(in_out);
		close_inout(cmd->in_out);
		close_pipe(g_sys.pipeline.fd);
		if (my_execve(cmd) == -1)
			exit(print_error_msg(cmd));
	}
	return (cmd->pid);
}

//=== extract_command ==========================================================
void	extract_command(t_node *cmd)
{
	char	**args;
	char	*tmp;

	if (((t_command *) cmd)->args)
		return ;
	tmp = get_cmd_name(cmd);
	args = expand_line(tmp); 
	if (args != NULL)
	{
		set_cmd_args(cmd, args);
		set_cmd_name(cmd, *args);
		set_cmd_path(cmd, whereis_cmd(*args));
	}
	free(tmp);
}

//=== get_command_inout ========================================================
int	*get_command_inout(t_list *file)
{
	int	*in_out;
	int	type;

	in_out = (int *) malloc(sizeof(int) * 2);
	ft_memset(in_out, 255, 8);
	while (in_out && file)
	{
		type = get_file_type(file);
		if (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND)
			set_file_fd(file, open(get_file_name(file), GET_MODE(type), 0644));
		if (get_file_fd(file) < -1)
			continue ;
		if ((type == REDIR_IN && get_file_type(file->next) != REDIR_IN)
				|| (type == HERE_DOC && get_file_type(file) != HERE_DOC))
			in_out[0] = get_file_fd(file);
		if ((type == REDIR_APPEND && get_file_type(file->next) != REDIR_APPEND)
				|| (type == REDIR_OUT && get_file_type(file->next) != REDIR_OUT))
			in_out[1] = get_file_fd(file);
		file = file->next;
	}
	return (in_out);
}

//=== dup_process_inout ========================================================
int	dup_process_inout(int *in_out)
{
	if (g_sys.pipeline.offset > -1 && in_out[0] == -1)
		dup2(g_sys.pipeline.offset, 0);
	if (in_out[0] > -1)
		dup2(in_out[0], 0);
	if (g_sys.pipeline.fd[1] > -1)
		dup2(g_sys.pipeline.fd[1], 1);
	if (in_out[1] > -1)
		dup2(in_out[1], 1);
	free(in_out);
	return (SUCCESS);
}
