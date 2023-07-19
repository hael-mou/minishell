/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:17:17 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/19 15:24:27 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include <unistd.h>

# define FAILURE 0
# define SUCCESS 1
# define TRUE 1
# define FALSE 0

typedef struct s_pipeline
{
				int fd[2];
				int	offset;
}				t_pipeline;

int		create_pipe(t_pipeline *pipeline, int boolval);
int		update_pipeline(t_pipeline *pipeline);
void	close_pipe(int *pipe);

#endif
