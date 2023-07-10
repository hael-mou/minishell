/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:16:20 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/10 22:50:13 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

# define GET_MODE(T) (O_CREAT | O_WRONLY | (T == REDIR_APPEND) * O_APPEND)

char	**get_env(t_list *g_env)
{
	char	**env;
	int		i;

	env = malloc(sizeof(char *) * (ft_lstsize(g_env) + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (g_env)
	{
		env[i++] = ft_strdup((char *) g_env->content);
		g_env = g_env->next;
	}
	env[i] = NULL;
	return (env);
}

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

int	close_all_fd(t_list *file, int *fd)
{
	while (file)
	{
		int re = close(get_file_fd(file));
		printf("RE| => %d\n", re);
		file = file->next;
	}
	close(fd[0]);
	close(fd[1]);
	return (SUCCESS);
}
