/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:39:37 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/06 22:16:03 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

t_pipe	*create_pipes(void)
{
	t_pipe	*pipes;
	int		i;

	pipes = (t_pipe *) malloc(sizeof(t_pipe) * 2);
	if (!pipes)
		return (NULL);
	i = -1;
	while (++i < 2)
		if (pipe(pipes[i].pipe) == -1)
			return (perror(0), NULL);
	pipes[0].next = &pipes[1];
	pipes[1].next = NULL;
	return (pipes);
}

t_pipe	*swap_pipes(t_pipe *pipes)
{
	t_pipe	*tmp;

	if (!pipes)
		return (NULL);
	tmp = pipes->next;
	pipes->next = NULL;
	tmp->next = pipes;
	return (tmp);
}

int	get_read_end(t_pipe *pipe)
{
	return (pipe->pipe[0]);
}

int	get_write_end(t_pipe *pipe)
{
	return (pipe->pipe[1]);
}
