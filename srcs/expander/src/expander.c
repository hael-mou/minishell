/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:28:53 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/25 08:38:06 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//=== expand var ========================================================
char	**expand_var(char *line)
{
	char	**eline;
	char	*tmp;
	int		len;

	tmp = ft_strdup("");
	while (line != NULL && *line != 0)
	{
		if (*line == '\'')
		{
			len = ft_toklen(++line, '\'');
			tmp = ft_strnjoin(tmp, line, len);
			line += len + 1;
		}
		else if (*line == '"')
			tmp = join_string(tmp, &line, TRUE);
		else
			tmp = join_string(tmp, &line, FALSE);
	}
	eline = ft_split(tmp, '\5');
	return (free(tmp), eline);
}

//=== expand heredoc ========================================================
char	*expand_heredoc(char *line)
{
	char	*eline;

	eline = ft_strdup("");
	while (line != NULL && *line != 0)
	{
		if (*line == '$')
		{
			eline = join_var(eline, &line, FALSE);
			continue ;
		}
		eline = ft_strnjoin(eline, line, 1);
		line++;
	}
	return (eline);
}

//=== expand heredoc ========================================================
void	set_home_path(char **arg)
{
	free(*arg);
	*arg = search_var(g_sys.env, "HOME");
	if (*arg == NULL)
	*arg = ft_strdup("/");
}

int	star_detected(char *arg)
{
	while (arg != NULL && *arg != 0)
	{
		if (*arg == '\2')
			return (TRUE);
		arg++;
	}
	return (FAILURE);
}

// char **expand_star(char **args, int *index)
// {
// 	t_dir	dir;
// 	char	*tmp;
// 	char	*file_name;

// 	tmp = ft_strdup("");
// 	dir.stream = opendir(".");
// 	if(dir.stream == NULL)
// 		return (FAILURE);
// 	dir.info = readdir(dir.stream);
// 	while (dir.info)
// 	{
// 		file_name = dir.info->d_name;
// 		if (ismatch(file_name, args[*index]))
// 			tmp = ft_vstrjoin(3, tmp, file_name, '\3');
// 		dir.info = readdir(dir.stream);
// 	}
// 	new_list = ft_split(tmp, '\3');
// 	new_list = merge(args, new_list);

// }

// char	**expand_wildcard(char **args)
// {
// 	int	index;

// 	index = 0;
// 	while (args != NULL && args[index] != NULL)
// 	{
// 		if (ft_strcmp(args[index], "~") == 0)
// 		{
// 			set_home_path(&args[index]);
// 		}
// 		else if (star_detected(args[index]) == TRUE)
// 		{
// 			args = expand_star(args, &index);
// 		}
// 		index++;
// 	}
// 	return (args);
// }
