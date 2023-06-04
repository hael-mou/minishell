/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 07:37:55 by hael-mou          #+#    #+#             */
/*   Updated: 2023/06/04 10:08:52 by hael-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/*###############################################################
#  	   * Includes :		    								 	#
###############################################################*/
# include "libft.h"
# include "types.h"

/*###############################################################
#  	   * define :		    								 	#
###############################################################*/
# define AND_IN_FUTURE 22
// # ifndef BONUS
// #  define BONUS 1
// # endif

/*###############################################################
#  	   * types :		    								 	#
###############################################################*/
typedef struct s_state
{
	char	*key;
	int		state;
}	t_state;

/*###############################################################
#  	   * Functions :											#
###############################################################*/
// minishell toknizer
t_list	*tokenizer(char *line);

// state utils 1:
int		state_start(char *input);
int		state_string(char *input);
int		state_quates(char *input, int prv_state);

// state utils 2:
int		state_pipe(char *input);
int		state_redout(char *input);
int		state_redin(char *input);

// tokenizer utils:
int		get_next_state(int state, char *input);
void	set_state(t_state *states, int index, char *key, int state);
int		get_state(t_state *states, int size, char input);
t_token	*create_token(char *start, char *end, int type);
t_list	*listadd_token(t_list **list, t_token *new_token);

#endif /* TOKENIZER_H */
