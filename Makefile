# **************************************************************************** #
#                              MAKEFILE                                        #
# **************************************************************************** #

# Variables
NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -O3
SRCS_DIR    = srcs
OBJS_DIR    = obj
MLX_DIR     = minilibx
LIBFT_DIR   = libft

# Libraries
MLX_LIB     = $(MLX_DIR)/libmlx.a
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

# Source files
SRCS        = parsing/copy_map.c \
              parsing/is_valid_map.c \
              parsing/parse_struct.c \
              rendering/minimap.c \
              rendering/window.c \
              main.c

# Génération des chemins complets
SRCS       := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS       := $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Commandes principales
all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB) $(LIBFT_LIB) -lXext -lX11 -lm

# Compilation des objets avec création des sous-dossiers
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)  # Crée automatiquement les sous-dossiers
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation des libraries
$(MLX_LIB): force
	make -C $(MLX_DIR)

$(LIBFT_LIB): force
	make -C $(LIBFT_DIR)

# Nettoyage
clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re force
