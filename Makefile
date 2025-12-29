# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkaras-g <bkaras-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 14:08:56 by bkaras-g          #+#    #+#              #
#    Updated: 2025/12/29 16:24:00 by bkaras-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = philo

SRC_DIR = src

SRC_FILES = main.c \
			wisdom_lovers_life.c \
			solitary_life.c \
			init.c \
			parsing.c \
			init2.c \
			utils.c \
			monitor.c \
			cleanup.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

RM = rm -f
OBJ := $(patsubst %.c, %.o, $(SRC))
CC = cc
FLAGS = -Wall -Wextra -Werror -ggdb
HEADER = includes/philo.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER) Makefile
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo  "Mandatory part compilation ok"

%.o: %.c
	@$(CC) $(FLAGS) -I. -c $< -o $@

clean:
# 	@$(MAKE) clean 1>/dev/null
	@$(RM) $(OBJ)
	@echo  "Clean done"

fclean: clean
# 	@$(MAKE) fclean 1>/dev/null
	@$(RM) $(NAME)

re: fclean all

dev: all clean

.PHONY: all clean fclean re dev
