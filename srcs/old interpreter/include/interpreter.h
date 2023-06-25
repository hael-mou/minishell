/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:38:00 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/21 13:20:32 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include "builtins.h"
# include "tokenizer.h"
# include "parser.h"

int		interpreter(t_node *root);

int		exec_cmds(t_node *node);
int		exec_subshell(t_node *node);
pid_t	exec_cmd(t_node *node);

/*********** UTILS **************/
char	**get_env(t_list *g_env);
#endif
