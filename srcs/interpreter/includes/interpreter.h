/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:38:00 by oezzaou           #+#    #+#             */
/*   Updated: 2023/07/12 22:55:14 by oezzaou          ###   ########.fr       */
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

/*###############################################################
#  	   * DEFINES   :											#
###############################################################*/
# define LEFT	2
# define RIGHT	3
# define FIRST_PART 1
# define SECOND_PART -1
# define GET_MODE(T) (O_CREAT | O_WRONLY | (T == REDIR_APPEND) * O_APPEND)

# define CMD_NOT_FOUND "Minishell: command not found"
# define PERMISSION_DIEND "Minishell: permission diend"
/*###############################################################
#  	   * Functions :											#
###############################################################*/
// interpreter :
int		interpreter(t_node *tree);

int		exec_branch(t_node *node);
int		exec_subshell(t_node *node);

// exec_cmd :
pid_t	exec_cmd(t_command *cmd, int permission);
void	extract_command(t_node *cmd);
pid_t	exec_builtins(t_command *cmd, int start);
int		*get_command_inout(t_list *cursor);
int		dup_process_inout(int *fd, int *in_out, int permission);
void	update_pipeline(int *fd, int p_type);

// interpreter_utils :
char	**get_env(t_list *g_env);
char	*whereis_cmd(char *cmd);
int		close_all_fd(t_list *files, int *fd);
int		print_error_msg(t_command *cmd);
#endif
