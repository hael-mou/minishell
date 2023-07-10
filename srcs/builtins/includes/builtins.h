/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:06:23 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/05 21:00:48 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/*#############################################################################
#		* Includes : 	    												  #
#############################################################################*/
# include <stdio.h>
# include "libft.h"
# include "defines.h"
# include "types.h"
# include "var.h"

/*#############################################################################
#		* Defines : 	    												  #
#############################################################################*/
# define MUTY_ARG	"too many arguments\n"
# define NONUM_ARG	"numeric argument required\n"
# define OLDPWD_ER	"OLDPWD not set\n"
# define CLEAR      "\033[2J\033[H"

/*#############################################################################
#		* Typedef : 	    												  #
#############################################################################*/

/*#############################################################################
#		* Functions : 	    												  #
#############################################################################*/
//int		exec_builtins(char *name, char **args);

// builtins function :
int		minishell_echo(char **args);
int		minishell_cd(char **args);
int		minishell_pwd(char **args);
int		minishell_export(char **args);
int		minishell_unset(char **args);
int		minishell_env(char **args);
int		minishell_exit(char **args);
void	clear(void);

#endif /* BUILTINS_H */
