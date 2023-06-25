/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:31:09 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/25 07:19:35 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft.h"
# include "var.h"
# include "defines.h"
# include "types.h"
# include <dirent.h>

typedef struct dirent	t_dirent;
typedef struct s_dir
{
	DIR			*stream;
	t_dirent	*info;
}	t_dir;

char	*join_string(char *eline, char **line, int in_dquote);
char	*join_var(char *eline, char **line, int in_dquote);
char	*get_var_key(char **line);


#endif /* EXPANDER_H */