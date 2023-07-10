/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_setters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:13:25 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/05 22:54:05 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

//=== set file name ===========================================================
void	set_file_name(t_list *file, char *name)
{
	if (file != NULL)
	{
		((t_file *)file->content)->name = name;
	}
}

//=== set file type ===========================================================
void	set_file_type(t_list *file, int type)
{
	if (file != NULL)
	{
		((t_file *)file->content)->type = type;
	}
}

//=== set_file_fd ===========================================================
void	set_file_fd(t_list *file, int nfd)
{
	if (file != NULL)
		((t_file *)file->content)->fd = nfd;
}
