/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:28:53 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/25 06:34:15 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//=== join string ========================================================
char	*join_string(char *eline, char **line, int in_dquote)
{
	if (eline == NULL || line == NULL)
		return (NULL);
	*line += in_dquote;
	while (*line != NULL && **line != 0 && **line != '"'
		&& (**line != '\'' || in_dquote))
	{
		if (**line == '$')
			eline = join_var(eline, line, in_dquote);
		else
		{
			if (**line == '*' && !in_dquote)
				eline = ft_strnjoin(eline, "\2", 1);
			else
				eline = ft_strnjoin(eline, *line, 1);
			(*line)++;
		}
	}
	*line += in_dquote;
	return (eline);
}

//=== join var ========================================================
char	*join_var(char *eline, char **line, int in_dquote)
{
	char	*key;
	char	*value;

	*line += 1;
	if (**line == 0)
		return (ft_strnjoin(eline, "$", 1));
	key = get_var_key(line);
	value = ft_strdup(search_var(g_sys.env, key));
	if (key == NULL || value == NULL)
		return (free(key), free(value), eline);
	if (in_dquote == FALSE)
	{
		ft_strreplace(value, " \t", '\5');
		ft_strreplace(value, "*", '\2');
	}
	eline = ft_strjoin(eline, value);
	*line += ft_strlen(key);
	return (free(key), eline);
}

//=== get var key ========================================================
char	*get_var_key(char **line)
{
	int		len;
	char	*key;

	len = ft_isalpha(**line);
	if (len == 0 && **line != 0)
		return (++(*line), NULL);
	while (ft_isalnum((*line)[len]))
		len++;
	key = ft_substr(*line, 0, len);
	line += len;
	return (key);
}
