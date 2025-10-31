# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 17:17:36 by rbardet-          #+#    #+#              #
#    Updated: 2025/04/03 12:58:49 by rbardet-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = MLX42
MLX = $(MLX_DIR)/build/libmlx42.a

FULL_CFLAGS = $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR)

SRC_DIR = srcs
OBJ_DIR = obj

SRCS = srcs/main.c \
		srcs/parsing/get_rgb.c \
		srcs/parsing/copy_map.c \
		srcs/parsing/is_valid_map.c \
		srcs/parsing/flood_fill.c \
		srcs/parsing/parse_struct.c \
		srcs/parsing/parse_utils.c \
		srcs/parsing/load_png.c \
		srcs/bonus/minimap.c \
		srcs/bonus/animated_sprite.c \
		srcs/bonus/door.c \
		srcs/movement/handle_movement.c \
		srcs/movement/movement.c \
		srcs/movement/rotate.c \
		srcs/raycasting/draw.c \
		srcs/raycasting/raycast.c \
		srcs/raycasting/calculate_ray.c \
		srcs/utils/manage_struct.c \
		srcs/utils/debug.c \
		srcs/utils/debug2.c

OBJS = $(SRCS:srcs/%.c=obj/%.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "$(BLUE)Compilation de la libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compilée avec succès !$(RESET)"

$(MLX):
	@echo "$(BLUE)Compilation de la ML42...$(RESET)"
	@cd $(MLX_DIR) && cmake -B build
	@cd $(MLX_DIR) && cmake --build build -j4
	@echo "$(GREEN)ML42 compilée avec succès !$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compilation de $<...$(RESET)"
	@$(CC) $(FULL_CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Création de l'exécutable $(NAME)...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -L$(MLX_DIR)/build -lmlx42 -ldl -lglfw -pthread -lm
	@echo "$(GREEN)Compilation de $(NAME) terminée avec succès !$(RESET)"
	@echo "\033[2J\033[1;1H\033[33m"
	@echo "\033[33m █████╗ ██╗   ██╗██████╗   \033[31m ██████╗ ██████╗ "
	@echo "\033[33m██╔══██╗██║   ██║██╔══██╗  \033[31m ╚════██╗██╔══██╗"
	@echo "\033[33m██║  ╚═╝██║   ██║██████╦╝  \033[31m  █████╔╝██║  ██║"
	@echo "\033[33m██║  ██╗██║   ██║██╔══██╗  \033[31m  ╚═══██╗██║  ██║"
	@echo "\033[33m╚█████╔╝╚██████╔╝██████╦╝  \033[31m ██████╔╝██████╔╝"
	@echo "\033[33m ╚════╝  ╚═════╝ ╚═════╝   \033[31m ╚═════╝ ╚═════╝ "
	@echo "\033[33mMon premier RayCaster avec la minilibX \n\033[0m"

clean:
	@echo "$(RED)Suppression des fichiers objets...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean 2>/dev/null || true
	@make -C $(MLX_DIR) clean 2>/dev/null || true
	@echo "$(GREEN)Nettoyage terminé !$(RESET)"

fclean: clean
	@echo "$(RED)Suppression de l'exécutable $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)Nettoyage de la libft...$(RESET)"
	@make -C $(LIBFT_DIR) fclean 2>/dev/null || true
	@echo "$(RED)Nettoyage de la MLX42...$(RESET)"
	@make -C $(MLX_DIR) fclean 2>/dev/null || true
	@echo "$(GREEN)Nettoyage complet terminé !$(RESET)"

re: fclean all

.PHONY: all clean fclean re
