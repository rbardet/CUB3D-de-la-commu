# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 22:28:21 by rbardet-          #+#    #+#              #
#    Updated: 2025/03/24 20:15:04 by rbardet-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC_DIR = src
PARSE_DIR = $(SRC_DIR)/parsing
RENDER_DIR = $(SRC_DIR)/rendering

SOURCES = $(SRC_DIR)/main.c \
		$(PARSE_DIR)/copy_map.c \
		$(PARSE_DIR)/parse_struct.c \
		$(PARSE_DIR)/is_valid_map.c \
		$(RENDER_DIR)/minimap.c \
		$(RENDER_DIR)/window.c \

INCLUDE = -I sources -I minilibx-linux -I LIBFT_V2

OBJ_DIR = obj
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

LIBXPATH = minilibx-linux
LIBX = $(LIBXPATH)/libmlx.a

LIBFTPATH = libft
LIBFT = $(LIBFTPATH)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)
LDFLAGS = -L$(LIBXPATH) -L$(LIBFTPATH) -lmlx -lX11 -lXext

all: $(LIBX) $(LIBFT) $(NAME)

$(NAME): $(OBJECTS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBX) $(LIBFT) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(LIBX):
	$(MAKE) -C $(LIBXPATH)

$(LIBFT):
	$(MAKE) -C $(LIBFTPATH)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBXPATH) clean
	$(MAKE) -C $(LIBFTPATH) clean

fclean: clean
	rm -f $(NAME) $(LIBX) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re

