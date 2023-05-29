# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-mou <hael-mou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/28 09:46:30 by hael-mou          #+#    #+#              #
#    Updated: 2023/05/29 18:50:53 by hael-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:=	minishell
BONUS 		:=	minishell_bonus

# Directories:
SRC_DIR		:=	srcs
LIBFT_DIR	:=	libft
LEXER_DIR	:=	minishell_lexer
BUILTIN_DIR	:=	builtins
OBJ_DIR		:=	objs
OBJ_DIRS	:=	$(OBJ_DIR)\
				$(OBJ_DIR)/$(BUILTIN_DIR)\
				$(OBJ_DIR)/$(LEXER_DIR)

# Libraries:
LIBFT		:=	$(LIBFT_DIR)/libft.a

# Files:
SRC			:=	minishell var_utils
BUILTIN 	:=	export env
LEXER		:=	Minishell_Lexer MandatoryState
SRC_FILES   :=	$(addprefix $(BUILTIN_DIR)/,$(BUILTIN))
SRC_FILES   +=	$(addprefix $(LEXER_DIR)/,$(LEXER))

SRC_FILES   :=	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC_FILES)))
SRC_FILES   +=	$(addprefix $(SRC_DIR)/,$(addsuffix .c,$(SRC)))
OBJ_FILES   :=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Command:
CC			:= cc
AR			:= ar rc
RM			:= rm -rf
CFLAGS 		:= -Wall -Wextra -Werror #-g -fsanitize=address
LINKS		:= -lreadline
INCLUDE     := -I includes \
               -I $(LIBFT_DIR)/includes \
               -I $(SRC_DIR)/$(LEXER_DIR)

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
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .create_dirs
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(GREEN) [OK]$(DEF)	$(CYAN)Compiling$(DEF) $<"

# Targets:
all: $(NAME)

bonus: $(BONUS)

$(BONUS): $(LIBFT) $(OBJ_FILES)
	@touch $@
	@echo "$(GREEN) [OK]$(DEF)	$(PURPLE)[ minishell_bonus is created ]$(DEF)"

$(NAME): $(LIBFT) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(LINKS) $(INCLUDE) $^ -o $@
	@echo "$(GREEN) [OK]$(DEF)	$(PINK)[ minishell is created ]$(DEF)"

$(LIBFT): $(LIBFT_DIR)
	@echo "$(GRAY)   # LIBFT :"
	@make -s -C $<
	@echo "$(GRAY)   # minishell :"

clean:
	@make -C $(LIBFT_DIR) clean
	@if [ -d $(OBJ_DIR) ]; then\
		$(RM) $(OBJ_DIR);\
		echo "$(GREEN) [OK]$(DEF)	$(RED)Minishell  Object files cleaned!$(DEF)";\
	fi

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@if [ -f $(NAME) ]; then\
		$(RM) $(NAME);\
		echo "$(GREEN) [OK]$(DEF)	$(RED)Minishell file cleaned!$(DEF)";\
	fi
	@if [ -f $(BONUS) ]; then\
		$(RM) $(BONUS);\
		echo "$(GREEN) [OK]$(DEF)	$(RED)minishell_bonus file cleaned!$(DEF)";\
	fi

re: fclean all

.create_dirs: $(OBJ_DIRS)

$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIRS)

.PHONY: all clean fclean re bonus