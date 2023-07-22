/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:37:38 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/22 16:59:42 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//===================
void	run_heredoc(t_list *file)
{
	pid_t	h_pid;
	int		h_pipe[2];

	if (pipe(h_pipe) == ERROR)
		perror("heredoc: create pipe error !!\n");
	else
	{
		h_pid = fork();
		if (h_pid < 0)
		{
			perror("heredoc: fock error !!\n");
			return ;
		}
		else if (h_pid == 0)
		{
			heardoc_readlines(file, h_pipe[1]);
			close_pipe(h_pipe);
			exit(SUCCESS);
		}
		set_file_fd(file, h_pipe[0]);
		close(h_pipe[1]);
		waitpid(h_pid, NULL, 0);
	}
}

//==================
void	heardoc_readlines(t_list *file, int fd)
{
	char	*line;
	int		detect_quotes;

	detect_quotes = remove_quotes(file);
	while (TRUE)
	{
		line = readline("heredoc> ");
		if (!ft_strcmp(line, get_file_name(file)))
			break ;
		line = ft_strjoin(line, ft_strdup("\n"));
		if (detect_quotes == FALSE)
			line = expand_heredoc(line);
		ft_putstr_fd(line, fd);
		free(line);
	}
}

//==================
int	remove_quotes(t_list *file)
{
	char	*name;
	char	*delm;
	char	*tmp;
	int		detect_quotes;

	detect_quotes = FALSE;
	delm = ft_strdup("");
	name = get_file_name(file);
	while (name != NULL && *name != 0)
	{
		if ((*name == DOUBLE_QUOTE || *name == SINGLE_QUOTE))
		{
			tmp = ft_strtok(name + 1, *name);
			name += ft_strlen(tmp) + 2;
			delm = ft_strjoin(delm, tmp);
			detect_quotes = TRUE;
			continue ;
		}
		delm = ft_strnjoin(delm, name++, 1);
	}
	free(get_file_name(file));
	set_file_name(file, delm);
	return (detect_quotes);
}
