/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:38:00 by oezzaou           #+#    #+#             */
/*   Updated: 2023/06/25 12:09:54 by hael-mou         ###   ########.fr       */
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
# include "builtins.h"
# include "parser.h"

/*###############################################################
#  	   * Functions :											#
###############################################################*/
// interpreter :
void	interpreter(t_node *tree);

// extract_cmd
void	extract_command(t_node *cmd);
char	*whereis_cmd(char *cmd);

#endif
