# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 09:16:42 by hael-mou          #+#    #+#              #
#    Updated: 2023/06/03 19:38:56 by hael-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TOKENIZER 	:= tokenizer
BONUS 		:= 1

CC			:= 	cc
SRC			:=	test/test tokenizer tokenizer_utils minishell_state1\
				minishell_state2
OBJ			:= 	$(addsuffix .o, $(SRC))
SRC			:= 	$(addsuffix .c, $(SRC))
LIBFT_DIR	:= 	../../libft
LIBFT		:= 	$(LIBFT_DIR)/libft.a
INC			:= 	-I $(LIBFT_DIR)/includes -I../../includes -I.
CFLAG		:= 	-Wall -Wextra -Werror -g -fsanitize=address
BB			= 0

all:  $(TOKENIZER)
	clear
	./$<

$(TOKENIZER): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAG) -lreadline $(INC) $(OBJ) $(LIBFT) -o $@
	@echo "------- mandatory lexer test created -------\n"

%.o: %.c
	@$(CC) $(CFLAG) -D BONUS=$(BONUS) $(INC) -c $< -o $@
	@echo "Compiling $<"

$(LIBFT):
	@echo "=> libft : "
	@make -C $(LIBFT_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf *.o */*.o

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(MANDATORY)

re: fclean clean all BONUS