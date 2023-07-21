/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:16:58 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/21 20:28:53 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipe.h"
# include <stdio.h>

//=== create_pipe =============================================================
int	create_pipe(t_pipeline *pipeline, int boolval)
{
	if (boolval)
		pipe(pipeline->fd);
	return (SUCCESS);
}

//=== close_pipe ==============================================================
void	close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

//=== update_pipeline =========================================================
int	update_pipeline(t_pipeline *pipeline)
{
	if (pipeline->fd[0] > -1 && pipeline->fd[1] > -1)
	{
		close(pipeline->offset);
		pipeline->offset = dup(pipeline->fd[0]);
		close_pipe(pipeline->fd);
		pipeline->fd[0] = -1;
		pipeline->fd[1] = -1;
	}
	return (SUCCESS);
}
