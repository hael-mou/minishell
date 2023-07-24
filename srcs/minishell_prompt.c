/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:34:12 by hael-mou          #+#    #+#             */
/*   Updated: 2023/07/24 17:31:08 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ICON_SUCCESS   "🟢"
#define ICON_FAILURE   "🔴"
#define ICON_PROMPT	   " ︻╦̵̵̿╤── 💥 ⟹  "
#define PROMPT_GIT	   "\033[1;34m git:(\033[1;31mmain\033[1;34m)"
#define PROMPT_SUFFIX  "\033[1;33m ✗"


//=====================
char *get_wdir(void)
{
	char	*cwd_abs_path;
	char	*cwd;

	cwd_abs_path = getcwd(NULL, 0);
	if (cwd_abs_path == 0)
		cwd_abs_path = ft_strdup("Error");
	cwd = ft_strdup(ft_strrchr(cwd_abs_path, '/') + !(!*(cwd_abs_path + 1)));
	return (free(cwd_abs_path), cwd);
}

//=====================
char *get_git_tag(void)
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

//=====================
char *get_status_icon(void)
{
	if (g_sys.exit_status == EXIT_SUCCESS)
		return (ICON_SUCCESS);
	return (ICON_FAILURE);
}

//=====================
char	*minishell_prompt(void)
{
	char	*prompt;
	char	*cwd;
	char	*git;
	char	*status;

	cwd = get_wdir();
	git = get_git_tag();
	status = get_status_icon();
	printf("\n\033[1;96m╭ %s %s\033[0;120m\n", cwd, git);
	prompt = ft_vstrjoin(3, ft_strdup("╰ "), status, ICON_PROMPT);
	return (free(cwd), prompt);
}
