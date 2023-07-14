/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:17:17 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/14 18:25:54 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include <unistd.h>

# define FAILURE 0
# define SUCCESS 1

typedef struct s_pipeline
{
				int *fd;
				int	offset;
}				t_pipeline;

int		create_pipe(int *fd, int boolval);
void	close_pipe(int *pipe);
int		update_pipeline(t_pipeline *pipeline, int boolval);

#endif
