# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 09:16:42 by hael-mou          #+#    #+#              #
#    Updated: 2023/05/27 14:56:21 by hael-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MANDATORY 	:= lexerMandatory
BONUS 		:= lexerBONUS

CC			:= cc
SRC			:= test/test Minishell_Lexer MandatoryState
BSRC		:= test/test Minishell_Lexer BonusState
OBJ			:= $(addsuffix .o, $(SRC))
OBJB		:= $(addsuffix .o, $(BSRC))
SRC			:= $(addsuffix .c, $(SRC))
BSRC		:= $(addsuffix .c, $(BSRC))
LIBFT_DIR	:= ../libft
LIBFT		:= $(LIBFT_DIR)/libft.a
INC			:= -I $(LIBFT_DIR)/includes -I../includes -I.
CFLAG		:= -Wall -Wextra -Werror -g -fsanitize=address 

all: Mtest

Mtest: $(MANDATORY)
	clear
	./$<

$(MANDATORY): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAG) -lreadline $(INC) $(OBJ) $(LIBFT) -o $@
	@echo "------- mandatory lexer test created -------\n"

bonus: $(LIBFT) $(OBJB)
	@$(CC) $(CFLAG) -lreadline $(INC) $(OBJB) $(LIBFT) -o $@
	@echo "------- BONUS lexer test created -------\n"

%.o: %.c
	@$(CC) $(CFLAG) $(INC) -c $< -o $@
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