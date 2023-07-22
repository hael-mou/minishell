/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:28:53 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/22 17:06:10 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

//=== expand line : ===========================================================
char	**expand_line(char *line)
{
	char	**exp_line;
	char	**tmp;

	tmp = expand_var(line);
	exp_line = expand_wildcard(tmp);
	ft_free_array(tmp);
	return (exp_line);
}

//=== expand var : ============================================================
char	**expand_var(char *line)
{
	char	**exp_line;
	char	*tmp;

	tmp = ft_strdup("");
	while (line != NULL && *line != 0)
	{
		if (*line == SINGLE_QUOTE)
		{
			tmp = with_single_quates(tmp, &line);
			continue ;
		}
		if (*line == DOUBLE_QUOTE)
			tmp = join_string(tmp, &line, TRUE);
		else
			tmp = join_string(tmp, &line, FALSE);
	}
	exp_line = ft_split(tmp, C_SPACE);
	return (free(tmp), exp_line);
}

//=== expand wildcard : =======================================================
char	**expand_wildcard(char **arg)
{
	char	**exp_line;
	char	*tmp;

	tmp = ft_strdup("");
	while (arg && *arg)
	{
		if (ft_strchr(*arg, C_STAR) == NULL)
			tmp = ft_vstrjoin(3, tmp, *arg,S_SPACE);
		else
			tmp = ft_strjoin(tmp, extract_star(*arg));
		arg++;
	}
	exp_line = ft_split(tmp, C_SPACE);
	return (free(tmp), exp_line);
}

//===
char	*expand_heredoc(char *line)
{
	char	*exp_line;
	char	*save;

	save = line;
	exp_line = ft_strdup("");
	while(line != NULL && *line != 0)
	{
		if (*line == '$' && *(line + 1) != '"' && *(line + 1) != '\'' 
			&& *(line + 1) != '\n' && *(line + 1) != 0)
			exp_line = extract_var(exp_line, &line, TRUE);
		else
			exp_line = ft_strnjoin(exp_line, line++, 1);
	}
	return (free(save), exp_line);
}