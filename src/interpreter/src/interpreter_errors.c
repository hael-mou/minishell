//  ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣴⣶⣾⣿⣶⣶⣶⣶⣦⣤⣄⠀⠀⠀⠀⠀⠀⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢠⡶⠻⠛⠟⠋⠉⠀⠈⠤⠴⠶⠶⢾⣿⣿⣿⣷⣦⠄⠀⠀⠀    𓐓  interpreter_errors.c 𓐔           
//  ⠀⠀⠀⠀⠀⢀⠔⠋⠀⠀⠤⠒⠒⢲⠀⠀⠀⢀⣠⣤⣤⣬⣽⣿⣿⣿⣷⣄⠀⠀                                              
//  ⠀⠀⠀⣀⣎⢤⣶⣾⠅⠀⠀⢀⡤⠏⠀⠀⠀⠠⣄⣈⡙⠻⢿⣿⣿⣿⣿⣿⣦⠀      Dev: oezzaou <oussama.ezzaou@gmail.com> 
//  ⢀⠔⠉⠀⠊⠿⠿⣿⠂⠠⠢⣤⠤⣤⣼⣿⣶⣶⣤⣝⣻⣷⣦⣍⡻⣿⣿⣿⣿⡀                                              
//  ⢾⣾⣆⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇                                              
//  ⠀⠈⢋⢹⠋⠉⠙⢦⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇       Created: 2025/02/24 11:01:51 by oezzaou
//  ⠀⠀⠀⠑⠀⠀⠀⠈⡇⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇       Updated: 2025/02/24 11:03:26 by oezzaou
//  ⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⢀⣾⣿⣿⠿⠟⠛⠋⠛⢿⣿⣿⠻⣿⣿⣿⣿⡿⠀                                              
//  ⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⢠⣿⣟⣭⣤⣶⣦⣄⡀⠀⠀⠈⠻⠀⠘⣿⣿⣿⠇⠀                                              
//  ⠀⠀⠀⠀⠀⠱⠤⠊⠀⢀⣿⡿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠘⣿⠏⠀⠀                             𓆩♕𓆪      
//  ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠘⢧⡀⠀⠀⠸⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠐⠋⠀⠀⠀                     𓄂 oussama ezzaou𓆃  
//  ⠀⠀⠀⠀⠀⠘⠄⣀⡀⠸⠓⠀⠀⠀⠠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                              

#include "interpreter.h"

//===<[ print_error_msg: ]>=====================================================
int	print_error_msg(t_node *cmd)
{
	char	*name;
	int		exit;
	char	*merrno_msg;

	if (g_sys.merrno == -1)
		return (0);
	name = get_name(cmd);
	merrno_msg = get_merrno_msg(g_sys.merrno);
	exit = get_exit(g_sys.merrno);
	return (ft_print_error("minishell: %: %\n", name, merrno_msg), exit);
}

//===<[ get_name: ]>============================================================
char	*get_name(t_node *cmd)
{
	t_list	*file;
	char	*name;

	if (g_sys.merrno == 1 || g_sys.merrno == 2 || g_sys.merrno == 6)
		name = get_cmd_name(cmd);
	if ((g_sys.merrno >= 3 && g_sys.merrno <= 5) || g_sys.merrno == 7)
	{
		file = get_cmd_iofile(cmd);
		while (file && get_file_fd(file) > -1)
			file = file->next;
		name = get_file_name(file);
	}
	return (name);
}

//===<[ get_msg: ]>=============================================================
char	*get_merrno_msg(int merrno)
{
	if (merrno == 1)
		return (CMD_NOT_FOUND);
	if (merrno >= 2 && merrno <= 3)
		return (NO_SUCH_FILE);
	if (merrno == 7)
		return (AMBIGUOUS_REDIRECT);
	return (PERMISSION_DENIED);
}

//===<[ get_exit: ]>============================================================
int	get_exit(int merrno)
{
	int	exit;

	exit = 127;
	exit -= 126 * ((merrno >= 3 && merrno <= 5) || merrno == 7);
	exit -= (merrno == 6);
	return (exit);
}

//===<[ set_merrno: ]>==========================================================
void	set_merrno(char *cmd)
{
	g_sys.merrno = 2;
	if (access(cmd, F_OK) == 0)
		g_sys.merrno = 7 * -access(cmd, X_OK) - 1;
}
