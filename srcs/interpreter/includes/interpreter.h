/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:38:00 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/21 12:33:42 by oezzaou          ###   ########.fr       */
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
# include "pipe.h"
# include "operator.h"
# include "builtins.h"
# include "parser.h"
# include "expander.h"

/*###############################################################
#  	   * DEFINES   :											#
###############################################################*/

# define CMD_NOT_FOUND "Minishell: command not found"
# define PERMISSION_DIEND "Minishell: permission diend"

/*###############################################################
#  	   * Functions :											#
###############################################################*/
// interpreter :
int		interpreter(t_node *tree);

// exec :
pid_t	exec_simple_cmd(t_node *cmd);
pid_t	exec_branches(t_node *node);
pid_t	exec_subshell(t_node *node);
pid_t	exec_builtins(t_node *cmd);

// exec_cmd :
pid_t	exec_cmd(t_node *cmd);
void	extract_command(t_node *cmd);
int		*get_command_inout(t_list *cursor);
int		dup_process_inout(int *in_out);
int		extract_exit_status(t_node *node);

// interpreter_utils :
char	**get_env(t_list *g_env);
char	*whereis_cmd(char *cmd);
int		close_inout(t_list *files);
int		my_execve(t_node *cmd);
int		get_mode(int type);
int		print_error_msg(t_node *cmd);

#endif
