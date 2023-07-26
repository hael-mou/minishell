/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:35:28 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/26 21:51:10 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*#############################################################################
#		* Includes : 	    												  #
#############################################################################*/
# include <unistd.h>
# include <stdio.h>
# include "readline.h"
# include "history.h"
# include <stdlib.h>
# include "defines.h"
# include "types.h"

/*#############################################################################
#		* Shell Info : 	    												  #
#############################################################################*/
# define PROG_INFO		"Minishell 2023 [Version 1.0.0.0]."
# define DEVLOPERS		"Copyright © OEZZAOU && HAEL-MOU. All Rights Reserved."
# define CLEAR			"\033[2J\033[H"
# define ICON_SUCCESS	"🟢"
# define ICON_FAILURE	"🔴"
# define ICON_PROMPT	" ︻╦̵̵̿╤── 💥 ⟹  "
# define PROMPT_GIT		"\033[1;34m git:(\033[1;31mmain\033[1;34m)"
# define PROMPT_SUFFIX	"\033[1;33m ✗"
# define WAITE_COLOR	"\033[0;120m"
# define CYAN_COLOR	"\033[1;96m"

/*#############################################################################
#		* Struct :	 	    												  #
#############################################################################*/
typedef struct s_minish
{
	char        *input;
	t_list      *tokens;
	t_node      *tree;
}	t_minish;

/*#############################################################################
#		* Functions : 	    												  #
#############################################################################*/
// minishll utils:
void	minishell_init(char **env);
void	minishell_clean(t_minish *minish);
void	builtins_init(t_built *builtins);
void    minishell_ignore(int argc, char **argv);

// minishell Module :
char	*minishell_prompt(void);
t_list	*lexer(char *cmd_line);
t_node	*parser(t_list *tokens);
void	interpreter(t_node *tree);

// other :
int		minishell_export(char **args);
void	clean_tree(t_node *head);

#endif /* MINISHELL_H */
