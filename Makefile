# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: david-fe <david-fe@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 14:33:21 by david-fe          #+#    #+#              #
#    Updated: 2025/06/23 14:33:24 by david-fe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
RM			= rm -rf
CC_FLAGS 	= -Wall -Wextra -Werror -g
THREAD_FLAG = -pthread
OBJ_PATH 	= .obj
OBJ 		= $(addprefix $(OBJ_PATH)/, $(notdir $(SRC:.c=.o)))
SRC_PATH 	= srcs
SRC 		= $(addprefix $(SRC_PATH)/, main.c \
										utils.c \
										inits.c)

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CC_FLAGS) $(THREAD_FLAG) $(OBJ) -o $(NAME)
	@echo "[COMPILED]"

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_PATH)
	@echo "[DELETED OBJECTS]"

fclean: clean
	@$(RM) $(NAME)
	@echo "[DELETED EXECUTABLE]"

re: fclean all

.PHONY: all clean fclean re
