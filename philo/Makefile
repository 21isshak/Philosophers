# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iskaraag <iskaraag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 16:08:33 by iskaraag          #+#    #+#              #
#    Updated: 2024/11/05 17:11:28 by iskaraag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -pthread
#comment previous line and uncomment next line for sanitizer
#CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g -pthread
OBJ_DIR = objects
SRC_DIR = src
SRCS = main.c \
	initing.c \
	starting.c \
	philo.c \
	utils.c \
	philo_utils.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "\033[1;35mProgram and objects are created\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;33mObjects are cleaned\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[1;33mProgram is cleaned\033[0m"

re: fclean all

.PHONY: all clean fclean re
