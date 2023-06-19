# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 11:01:09 by hael-mou          #+#    #+#              #
#    Updated: 2023/06/19 09:33:07 by hael-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			:=	minishell
BONUS			:=	1

# Directories:
SRC_DIR			:=	srcs
LIBFT_DIR		:= 	libft
OBJ_DIR			:=	objs

# Libraries:
LIBFT			:=	$(LIBFT_DIR)/libft.a

# Files:
SRC_FILES		:=	$(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/src/*.c)
OBJ_FILES		:=	$(patsubst %.c,$(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))

# include:
INCLUDE_FILES	:= 	$(wildcard includes/*.h) $(wildcard */includes/*.h)\
					$(wildcard */*/includes/*.h)
INCLUDE_DIRS	:=	$(sort $(dir $(INCLUDE_FILES)))

# Command:
CC				:= 	cc
RM				:= 	rm -rf
CFLAGS 			:= 	-Wall -Wextra -Werror #-g -fsanitize=address
LINKS			:= 	-lreadline
INCLUDE			:=	$(addprefix -I,$(INCLUDE_DIRS))

# Colors :
DEF				= \033[0;39m
GRAY			= \033[0;90m
PINK			= \033[0;38;5;199m
RED				= \033[0;91m
GREEN			= \033[0;32m
CYAN			= \033[0;96m
PURPLE			= \033[0;35m
YELLOW			= \033[0;93m

# compiling Rules:
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .create_dirs
	@$(CC) $(CFLAGS) -D BONUS=$(BONUS) $(INCLUDE) -c $< -o $@
	@echo "$(GREEN) [OK]$(DEF)	$(PURPLE)Compiling$(DEF)  $<"

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/src/%.c | .create_dirs
	@$(CC) $(CFLAGS) -D BONUS=$(BONUS) $(INCLUDE) -c $< -o $@
	@echo "$(GREEN) [OK]$(DEF)	$(PURPLE)Compiling$(DEF)  $<"

.create_dirs: $(OBJ_DIR)

# role :
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(LINKS) $(INCLUDE) $^ -o $@
	@echo "$(GREEN) [OK]$(DEF)$(YELLOW)	[ $@ is created ]$(DEF)"

run:
	./$(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@if [ -d $(OBJ_DIR) ]; then\
		$(RM) $(OBJ_DIR);\
		echo "$(GREEN) [OK]$(DEF)	$(CYAN)$(NAME) Object files cleaned!$(DEF)";\
	fi

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@if [ -f $(NAME) ]; then\
		$(RM) $(NAME);\
		echo "$(GREEN) [OK]$(DEF)	$(RED)$(NAME) cleaned!$(DEF)";\
	fi

re: fclean all

$(LIBFT):
	@make -SC $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re run
