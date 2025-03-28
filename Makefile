# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 14:16:29 by rbardet-          #+#    #+#              #
#    Updated: 2025/03/28 14:27:58 by rbardet-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
SRCS_DIR    = srcs
OBJS_DIR    = obj
MLX_DIR     = MLX42
LIBFT_DIR   = libft

MLX_LIB     = $(MLX_DIR)/build/libmlx42.a
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

SRCS        = parsing/copy_map.c \
			  parsing/is_valid_map.c \
			  parsing/parse_struct.c \
			  parsing/parse_utils.c \
			  rendering/minimap.c \
			  rendering/window.c \
			  rendering/movement.c \
			  raycasting/draw.c \
			  raycasting/raycast.c \
			  raycasting/calculate_ray.c \
			  utils/debug.c \
			  utils/debug2.c \
			  main.c

SRCS       := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS       := $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)
	@echo "\033[2J\033[1;1H\033[33m"
	@echo "\033[33m █████╗ ██╗   ██╗██████╗   \033[31m ██████╗ ██████╗ "
	@echo "\033[33m██╔══██╗██║   ██║██╔══██╗  \033[31m ╚════██╗██╔══██╗"
	@echo "\033[33m██║  ╚═╝██║   ██║██████╦╝  \033[31m  █████╔╝██║  ██║"
	@echo "\033[33m██║  ██╗██║   ██║██╔══██╗  \033[31m  ╚═══██╗██║  ██║"
	@echo "\033[33m╚█████╔╝╚██████╔╝██████╦╝  \033[31m ██████╔╝██████╔╝"
	@echo "\033[33m ╚════╝  ╚═════╝ ╚═════╝   \033[31m ╚═════╝ ╚═════╝ "
	@echo "\033[33mMon premier RayCaster avec la minilibX \n\033[0m"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB) $(LIBFT_LIB) -ldl -lglfw -pthread -lm

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB): force
	@echo "Compiling MLX42..."
	@make -C $(MLX_DIR)/build

$(LIBFT_LIB): force
	@echo "Compiling Libft..."
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Cleaning objects..."

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaning executable..."

re: fclean all

.PHONY: all clean fclean re force
