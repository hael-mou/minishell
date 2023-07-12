/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:13:25 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/11 18:44:14 by oezzaou          ###   ########.fr       */
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

//=== get_file_fd =============================================================
int	get_file_fd(t_list *file)
{
	if (file != NULL)
		return (((t_file *)file->content)->fd);
	return (ERROR);
}
