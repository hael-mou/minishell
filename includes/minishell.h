/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:35:28 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/03 16:48:33 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*###############################################################
#		* Includes :		    							 	#
###############################################################*/
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "defines.h"
# include "libft.h"
# include "minishell_types.h"

// global var :
t_list  *env;

// ACTIVE BONUS
# ifndef BONUS
#  define BONUS 0
# endif

/*###############################################################
#		*  DEFINES :											#
###############################################################*/
// SHELL INFO :
# define PROGRAM_INFO   "Minishell 2023 [Version 1.0.0.0]."
# define DEVLOPERS  "Copyright © OEZZAOU && HAEL-MOU. All Rights Reserved."
/*###############################################################
#		* Functions :											#
###############################################################*/
// builtins :
void	shell_env(void);
void	export_show(void);
int 	shell_export(char *new_var);

// var utils :
t_var   *new_var(char *key, char *value);
t_list  *get_var(char *key);
char	*extract_key(char *env_var);
char	*extract_value(char *env_var);

#endif