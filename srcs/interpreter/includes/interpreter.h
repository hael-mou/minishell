/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:38:00 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/18 18:53:52 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H
# include "sys/wait.h"
# include "unistd.h"
# include "tokenizer.h"
# include "parser.h"

typedef struct s_pipe
{
	int				pipe[2];
	struct s_pipe	*next;
}					t_pipe;

int		interpreter(t_node *ast);
t_pipe	*create_pipes(void);
//t_pipe	*swap_pipes(t_pipe *pipes);
//int		get_read_end(t_pipe *pipe);
//int		get_write_end(t_pipe *pipe);

int		exec_cmds(t_node *node);
pid_t	exec_cmd(t_node *node);
int		exec_subshell(t_node *node);

#endif
