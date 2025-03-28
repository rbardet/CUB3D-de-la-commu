# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 16:03:56 by rbardet-          #+#    #+#              #
#    Updated: 2025/03/28 16:57:28 by rbardet-         ###   ########.fr        #
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

SRCS        := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS        := $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

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

$(MLX_LIB):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MLX42 repository..."; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	@echo "Running CMake for MLX42..."
	@cd $(MLX_DIR) && cmake -B build
	@echo "Building MLX42..."
	@cd $(MLX_DIR) && cmake --build build -j4

$(LIBFT_LIB):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Libft not found, cloning repository..."; \
		git clone https://github.com/rbardet/biglibft.git $(LIBFT_DIR); \
		cd $(LIBFT_DIR) && make; \
	fi
	@echo "Libft is already present, skipping build."

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Cleaning objects..."

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)
	@rm -rf $(LIBFT_DIR)
	@echo "Cleaning executable and libraries..."

re: fclean all

.PHONY: all clean fclean re
