/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:04:28 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/26 23:09:21 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/*#############################################################################
#		* Includes  	    												  #
#############################################################################*/
# include "list.h"
# include "pipe.h"
# include "builtins.h"
# include <dirent.h>

typedef struct s_built
{
	char	*name[8];
	int		(*func[8])(char **);
}				t_built;

/*#############################################################################
#		* System type  	    												  #
#############################################################################*/
typedef struct s_system
{
	int			std_in;
	int			std_out;
	int			exit_status;
	int			merrno;
	char		*prompt;
	t_list		*env;
	t_built		builtins;
	t_pipeline	pipeline;
}	t_system;

/*#############################################################################
#		* Node type	   	 		   											  #
#############################################################################*/
typedef struct s_node
{
	int			type;
	pid_t		pid;
}	t_node;

typedef struct dirent	t_dirent;
typedef struct s_dir
{
	DIR			*stream;
	t_dirent	*info;
}	t_dir;

/*#############################################################################
#		* Global Varable  	    											  #
#############################################################################*/
t_system				g_sys;

#endif /* TYPES_H */
