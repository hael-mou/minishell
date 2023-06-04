# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 09:16:42 by hael-mou          #+#    #+#              #
#    Updated: 2023/06/04 13:44:29 by hael-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:=	tokenizer
TEST		:=	tokenizer.test
BONUS		:=	0

# Directories:
SRC_DIR		:=	src
LIBFT_DIR	:= 	../../libft
OBJ_DIR		:=	objs

# Libraries:
LIBFT		:=	$(LIBFT_DIR)/libft.a

# Files:
SRC			:=	minishell_state1 minishell_state2\
				tokenizer_utils tokenizer
SRC_FILES	:=	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC)))
OBJ_FILES	:=	$(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(SRC)))

# Command:
CC			:= 	cc
AR			:= 	ar rc
RM			:= 	rm -rf
CFLAGS 		:= 	-Wall -Wextra -Werror -g -fsanitize=address
LINKS		:= 	-lreadline
INCLUDE     := 	-I$(LIBFT_DIR)/includes\
				-I../../includes\
				-I$(SRC_DIR) 

# Colors :
DEF			= \033[0;39m
GRAY		= \033[0;90m
PINK		= \033[0;38;5;199m
RED			= \033[0;91m
GREEN		= \033[0;32m
CYAN		= \033[0;96m
PURPLE		= \033[0;35m
YELLOW		= \033[0;93m

# compiling Rules:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/tokenizer.h | .create_dirs
	@$(CC) $(CFLAG) -D BONUS=$(BONUS) $(INCLUDE) -c $< -o $@
	@echo "$(GREEN) [OK]$(DEF)	$(PURPLE)Compiling$(DEF) $<"

# Targets:
all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(AR) $@ $^
	@echo "$(GREEN) [OK]$(DEF)	$(YELLOW)[ Tokenizer is created ]$(DEF)"

test: $(TEST) run

$(TEST): $(LIBFT) $(NAME)
	@$(CC) $(CFLAG) $(LINKS) $(INCLUDE) test/test.c $^ -o $@

run:
	clear
	./$(TEST)

clean:
	@make -C $(LIBFT_DIR) clean
	@if [ -d $(OBJ_DIR) ]; then\
		$(RM) $(OBJ_DIR);\
		echo "$(GREEN) [OK]$(DEF)	$(CYAN)Tokenizer Object files cleaned!$(DEF)";\
	fi

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@if [ -f $(NAME) ]; then\
		$(RM) $(NAME);\
		echo "$(GREEN) [OK]$(DEF)	$(RED)Tokenizer cleaned!$(DEF)";\
	fi
	@if [ -f $(TEST) ]; then\
		$(RM) $(TEST);\
		echo "$(GREEN) [OK]$(DEF)	$(RED)Tokenizer.test cleaned!$(DEF)";\
	fi

.create_dirs: $(OBJ_DIR)

$(LIBFT):
	@make -SC $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

re: fclean all