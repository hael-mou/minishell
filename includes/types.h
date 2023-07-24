/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:04:28 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/24 17:25:11 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/*##############################################################################
#		* Includes  	    												   #
##############################################################################*/
# include "list.h"
# include "pipe.h"
# include "builtins.h"
# include <dirent.h>

typedef struct s_built
{
	char	*name[8];
	int		(*func[8])(char **);
}				t_built;

/*##############################################################################
#		* System type  	    												   #
##############################################################################*/
typedef struct s_system
{
	t_list		*env;
	int			std_in;
	int			std_out;
	t_built		builtins;
	t_pipeline	pipeline;
	int			exit_status;
	int			merrno;
}	t_system;

/*##############################################################################
#		* Global Varable  	    											   #
##############################################################################*/
t_system	g_sys;

/*##############################################################################
#		* Node type	   	 		   											   #
##############################################################################*/
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

#endif /* TYPES_H */
