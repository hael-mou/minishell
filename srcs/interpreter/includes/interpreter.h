/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:38:00 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/09 17:36:46 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H

/*###############################################################
#  	   * Includes	:											#
###############################################################*/
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "builtins.h"
# include "parser.h"
# include "expander.h"

# define CLOSE	0
# define CREAT	1
# define LEFT	2
# define RIGHT	3

/*###############################################################
#  	   * Functions :											#
###############################################################*/
// interpreter :
int		interpreter(t_node *tree);

int		exec_cmds(t_node *node);
int		exec_subshell(t_node *node);
pid_t	exec_cmd(t_command *cmd, int position, int p_type);
int		*get_command_inout(t_list *cursor);
char	**get_env(t_list *g_env);
int		manage_pipe(int *pipe, int flag);
pid_t	exec_builtins(t_node *node);

// extract_cmd
void	extract_command(t_node *cmd);
char	*whereis_cmd(char *cmd);

#endif
