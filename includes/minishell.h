/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:35:28 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/18 08:49:54 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*###############################################################
#		* Includes :		    							 	#
###############################################################*/
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "defines.h"

/*###############################################################
#		*  Shell Info :											#
###############################################################*/
# define PROGRAM_INFO	"Minishell 2023 [Version 1.0.0.0]."
# define DEVLOPERS	"Copyright © OEZZAOU && HAEL-MOU. All Rights Reserved."

/*###############################################################
#		* Functions :											#
###############################################################*/
// Minishell Init :
void	minishell_info(void);
void	minishell_init(char **env);

// tokenizer :
void	*tokenizer(char *line);
void	clean_tokenizer(void *tokens);

// builtins :
int	    minishell_export(char *variable);
int		minishell_unset(char *var_name);

void	print_tokens(void *tokens); // remove
#endif