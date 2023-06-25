/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 08:55:32 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/25 01:57:16 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

/*###############################################################
#		* Includes :		    							 	#
###############################################################*/
# include "libft.h"
# include "defines.h"

/*###############################################################
#		* token Types :		    							 	#
###############################################################*/
typedef struct s_file
{
	int		type;
	char	*name;
	int		pipe;
}	t_file;

/*###############################################################
#		* Functions :		    							 	#
###############################################################*/
// file function :
t_file	*create_file(char *name, int type);
void	clean_file(void *content);
void	listadd_file(t_list **files, t_file *new_file);

// file setters :
void	set_file_name(t_list *file, char *name);
void	set_file_type(t_list *file, int type);
void	set_file_pipe(t_list *file, int pipe);

// file getters :
char	*get_file_name(t_list *file);
int		get_file_type(t_list *file);
int		get_file_type(t_list *file);

#endif /* FILE_H */
