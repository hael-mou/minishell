/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:13:25 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/25 01:39:27 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

//=== get file name ===========================================================
char	*get_file_name(t_list *file)
{
	if (file != NULL)
		return (((t_file *)file->content)->name);
	return (NULL);
}

//=== get file type ===========================================================
int	get_file_type(t_list *file)
{
	if (file != NULL)
		return (((t_file *)file->content)->type);
	return (ERROR);
}

//=== get file pipe ===========================================================
int	get_file_pipe(t_list *file)
{
	if (file != NULL)
		return (((t_file *)file->content)->pipe);
	return (ERROR);
}
