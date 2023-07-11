/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:50:04 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/11 19:18:09 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "interpreter.h"

//=== exec_cmd ================================================================
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
			exit(printf("Command Error ...\n"));
	}
	update_pipeline(fd, p_type);
	close_all_fd(cmd->in_out, fd);
	free(in_out);
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

	in_out = (int *) malloc(sizeof(int) * 2);
	ft_memset(in_out, 255, 8);
	while (in_out && file)
	{
		mode = GET_MODE(get_file_type(file));
		if (get_file_type(file) == REDIR_IN)
			set_file_fd(file, open(get_file_name(file), O_RDONLY));
		if (get_file_type(file) == REDIR_OUT || get_file_type(file) == REDIR_APPEND)
			set_file_fd(file, open(get_file_name(file), mode, 0644));
		if (get_file_type(file) == REDIR_IN && get_file_type(file->next) != REDIR_IN)
			in_out[0] = get_file_fd(file);
		// NEED TO USE ONE CONDITION FOR THESE TWO
		if ((get_file_type(file) == REDIR_OUT && get_file_type(file->next) != REDIR_OUT))
			in_out[1] = get_file_fd(file);
		if (get_file_type(file) == REDIR_APPEND && get_file_type(file->next) != REDIR_APPEND)
			in_out[1] = get_file_fd(file);
		// CASE OF HEREDOC
		file = file->next;
	}
	return (in_out);
}

//=== dup_process_inout =======================================================
int	dup_process_inout(int *fd, int *in_out, int position, int p_type)
{
	if (g_sys.pipeline > -1 && in_out[0] == -1)
		dup2(g_sys.pipeline, 0);
	if (in_out[0] > -1)
		dup2(in_out[0], 0);
	if (position == LEFT && p_type == PIPE)
		dup2(fd[1], 1);
	if (in_out[1] > -1)
		dup2(in_out[1], 1);
	return (SUCCESS);
}

//=== update_pipeline =========================================================
void	update_pipeline(int *fd, int p_type)
{
	if (p_type == PIPE)
	{
		close(g_sys.pipeline);
		g_sys.pipeline = dup(fd[0]);
	}
}
