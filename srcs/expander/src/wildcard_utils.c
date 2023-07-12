/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:52:16 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/12 20:25:54 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//=== home_path : =============================================================
char	*home_path(char *eline, char **line)
{
	char	*value;

	*line += 1;
	if (*(*line + 1) != '/' && *(*line + 1) != 0 && *(*line + 1) != C_SPACE)
		value = ft_strdup("~");
	else
	{
		value = ft_strdup(search_var(g_sys.env, "HOME"));
		if (value == NULL)
			value = ft_strdup("/");
	}
	eline = ft_vstrjoin(3, eline, S_SPACE, value);
	return (free(value), eline);
}

//=======
t_pattern	get_pattern(char *line)
{
	t_pattern	pattern;
	char		*tmp;

	tmp = line;
	pattern.first = ft_strtok(line, C_STAR);
	tmp += ft_strlen(pattern.first);
	tmp = ft_strrchr(tmp, C_STAR);
	if (*tmp != 0)
		pattern.last = ft_strdup(tmp + 1);
	*tmp = 0;
	pattern.middle = ft_split(line, C_STAR);
	free(line);
	return (pattern);
}

//========
int	is_match(char *str, t_pattern *pattern)
{
	int		len;
	char	**middle;

	middle = pattern->middle;
	len = ft_strlen(pattern->first);
	if (pattern->first != NULL && *(pattern->first) != 0
		&&ft_strncmp(str, pattern->first, len) != 0)
		return (FALSE);
	while (middle && *middle)
	{
		str = ft_strnstr(str, *middle, ft_strlen(str));
		if (str == NULL)
			return (FALSE);
		middle++;
	}
	len = ft_strlen(pattern->last);
	if (ft_strlen(str) - len >= 0)
	{
		str += ft_strlen(str) - len;
		if (pattern->last != NULL && *(pattern->last) != 0
			&& ft_strncmp(str, pattern->last, len) != 0)
		return (FALSE);
	}
	else
		return (FALSE);
	return (TRUE);
}

//========
char	*extract_star(char *line)
{
	t_pattern	pattern;
	t_dir		dir;
	char		*exp_line;

	pattern = get_pattern(ft_strdup(line));
	dir.stream = opendir(".");
	exp_line = ft_strdup("");
	if (dir.stream == NULL)
		return (NULL); //free pattern;
	dir.info = readdir(dir.stream);
	while (dir.info)
	{
		if (is_match(dir.info->d_name, &pattern))
			exp_line = ft_vstrjoin(3, exp_line, dir.info->d_name, S_SPACE);
		dir.info = readdir(dir.stream);
	}
	if (*exp_line == 0)
	{
		ft_strreplace(line, S_STAR, '*');
		exp_line = ft_vstrjoin(3, exp_line, line, S_SPACE);
	}
	//free pattern
	return (exp_line);
}
