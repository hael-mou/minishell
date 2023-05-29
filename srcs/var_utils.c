/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:03:23 by hael-mou          #+#    #+#             */
/*   Updated: 2023/05/29 19:38:11 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*new_var(char *key, char *value)
{
	t_var	*new_var;

	new_var = ft_calloc(1, sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	new_var->key = key;
	new_var->value = value;
	return (new_var);
}

t_list  *get_var(char *key)
{
    t_list  *env_tmp;
    t_var	*var;

    env_tmp = env;
    while (env_tmp != NULL)
    {
        var = env_tmp->content;
        if (ft_strcmp(var->key, key) == 0)
            return (env_tmp);
        env_tmp = env_tmp->next;
    }
    return (NULL);
}

char	*remove_quates(char *line)
{
	char	quote;
	int		len;

	len = 1;
	quote = *line;
	if (*line != '"' && *line != '\'')
		return (ft_strdup(line));
	while (line[len] && line[len] != quote)
		len++;
	return (ft_substr(line, 1, --len));
}

// !remove quates from key
char	*extract_key(char *env_var)
{
	int		len;
	
	if (env_var == NULL)
		return (NULL);
	len = -1;
	while (env_var[++len] && env_var[len] != '=')
		;
	return (ft_substr(env_var, 0, len));
}

char	*extract_value(char *env_var)
{
	char	*value;

	value = ft_strchr(env_var, '=');
	if (value == NULL)
		return (ft_strdup(""));
	return (remove_quates(++value));
}
