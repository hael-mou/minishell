/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_setters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:13:25 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/25 01:39:38 by hael-mou         ###   ########.fr       */
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

//=== set file type ===========================================================
void	set_file_pipe(t_list *file, int pipe)
{
	if (file != NULL)
	{
		((t_file *)file->content)->pipe = pipe;
	}
}
