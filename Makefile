# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 17:17:36 by rbardet-          #+#    #+#              #
#    Updated: 2025/03/31 18:03:38 by rbardet-         ###   ########.fr        #
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
		srcs/parsing/copy_map.c \
		srcs/parsing/is_valid_map.c \
		srcs/parsing/parse_struct.c \
		srcs/parsing/parse_utils.c \
		srcs/parsing/load_png.c \
		srcs/rendering/minimap.c \
		srcs/rendering/window.c \
		srcs/door/door.c \
		srcs/movement/handle_movement.c \
		srcs/movement/movement.c \
		srcs/movement/rotate.c \
		srcs/raycasting/draw.c \
		srcs/raycasting/raycast.c \
		srcs/raycasting/calculate_ray.c \
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
	@echo "$(BLUE)Téléchargement de la libft...$(RESET)"
	@git clone https://github.com/rbardet/biglibft.git $(LIBFT_DIR) 2>/dev/null || (cd $(LIBFT_DIR) && git pull)
	@echo "$(BLUE)Compilation de la libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compilée avec succès !$(RESET)"

$(MLX):
	@echo "$(BLUE)Téléchargement de la minilibx...$(RESET)"
	@git clone https://github.com/kodokaii/MLX42.git $(MLX_DIR) 2>/dev/null || (cd $(MLX_DIR) && git pull)
	@echo "$(BLUE)Compilation de la minilibx...$(RESET)"
	@cd $(MLX_DIR) && cmake -B build
	@cd $(MLX_DIR) && cmake --build build -j4
	@echo "$(GREEN)Minilibx compilée avec succès !$(RESET)"

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
	@if [ -d "$(LIBFT_DIR)" ]; then \
		echo "$(RED)Suppression du dossier libft...$(RESET)"; \
		rm -rf $(LIBFT_DIR); \
	fi
	@if [ -d "$(MLX_DIR)" ]; then \
		echo "$(RED)Suppression du dossier minilibx...$(RESET)"; \
		rm -rf $(MLX_DIR); \
	fi
	@echo "$(GREEN)Nettoyage complet terminé !$(RESET)"

re: fclean all

.PHONY: all clean fclean re
