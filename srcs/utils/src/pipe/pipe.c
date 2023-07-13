/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:16:58 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/13 20:01:33 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipe.h"
# include <stdio.h>

int	create_pipe(int *fd, int boolval)
{
	if (boolval)
		pipe(fd);
	return (SUCCESS);
}

void	close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

int	update_pipeline(t_pipeline *pipeline, int boolval)
{
	if (boolval)
	{
		close(pipeline->line);
		pipeline->line = dup(pipeline->fd[0]);
	}
	close_pipe(pipeline->fd);
	return (SUCCESS);
}
