/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:35:28 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/25 05:19:37 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*#############################################################################
#		* Includes : 	    												  #
#############################################################################*/
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include "defines.h"
# include "types.h"

/*#############################################################################
#		* Shell Info : 	    												  #
#############################################################################*/
# define PROG_INFO	"Minishell 2023 [Version 1.0.0.0]."
# define DEVLOPERS	"Copyright © OEZZAOU && HAEL-MOU. All Rights Reserved."
# define CLEAR      "\033[2J\033[H"

/*#############################################################################
#		* Functions : 	    												  #
#############################################################################*/
// minishell:
void	minishell_init(char **env);
void	minishell_clear(void);

// minishell utils :
t_list		*lexer(char *cmd_line);
t_node		*parser(t_list *tokens);
void		interpreter(t_node *tree);
int			minishell_export(char **args);

#endif /* MINISHELL_H */
