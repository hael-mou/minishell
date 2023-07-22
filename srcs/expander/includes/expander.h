/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:31:09 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/22 16:28:42 by hael-mou         ###   ########.fr       */
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

typedef struct s_pattern
{
	char	*first;
	char	*last;
	char	**middle;
}	t_pattern;

//=======================================
char	**expand_line(char *line);
char	**expand_var(char *line);
char	**expand_wildcard(char **arg);
char	*expand_heredoc(char *line);

//=======================================
char	*extract_var(char *eline, char **line, int in_dquote);
char	*get_var_key(char **line);
char	*var_value(char *key);

//======================================
char	*home_path(char *eline, char **line);
char	*extract_star(char *line);
void	clear_pattern(t_pattern *pattern);

//======================================
char	*with_single_quates(char *eline, char **line);
char	*join_string(char *eline, char **line, int in_dquote);

#endif /* EXPANDER_H */