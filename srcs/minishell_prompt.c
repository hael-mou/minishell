/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:34:12 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/26 20:39:02 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//=== get_wdir ================================================================
char	*get_wdir(void)
{
	char	*cwd_abs_path;
	char	*cwd;

	cwd_abs_path = getcwd(NULL, 0);
	if (cwd_abs_path == 0)
		cwd_abs_path = ft_strdup("Error");
	cwd = ft_strdup(ft_strrchr(cwd_abs_path, '/') + !(!*(cwd_abs_path + 1)));
	return (free(cwd_abs_path), cwd);
}

//=== get_git_tag =============================================================
char	*get_git_tag(void)
{
	t_dir	dir;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	dir.stream = opendir(cwd);
	free(cwd);
	if (dir.stream == NULL)
		return (ft_strdup(""));
	dir.info = readdir(dir.stream);
	while (dir.info)
	{
		if (ft_strcmp(dir.info->d_name, ".git") == 0)
			return (closedir(dir.stream), PROMPT_GIT);
		dir.info = readdir(dir.stream);
	}
	closedir(dir.stream);
	return (PROMPT_SUFFIX);
}

//=== get_status_icon =========================================================
char	*get_status_icon(void)
{
	if (g_sys.exit_status == EXIT_SUCCESS)
		return (ICON_SUCCESS);
	return (ICON_FAILURE);
}

//=== minishell_prompt ========================================================
char	*minishell_prompt(void)
{
	char	*prompt;
	char	*cwd;
	char	*git;
	char	*status;

	cwd = get_wdir();
	git = get_git_tag();
	status = get_status_icon();
	prompt = ft_strdup("\n"CYAN_COLOR"╭ ");
	prompt = ft_vstrjoin(4, prompt, cwd, git, WAITE_COLOR"\n");
	prompt = ft_vstrjoin(4, prompt, "╰ ", status, ICON_PROMPT);
	return (free(cwd), prompt);
}
