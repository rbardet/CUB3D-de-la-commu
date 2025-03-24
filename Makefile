# **************************************************************************** #
#                              MAKEFILE                                        #
# **************************************************************************** #

# Variables
NAME        = cub3d
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -O3 -lm
SRCS_DIR    = srcs
OBJS_DIR    = obj
MLX_DIR     = minilibX
LIBFT_DIR   = libft

# Libraries
MLX_LIB     = $(MLX_DIR)/libmlx.a
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

# Source files
SRCS        = $(SRCS_DIR)/fractals/burningship.c \
              $(SRCS_DIR)/fractals/mandelbar.c \
              $(SRCS_DIR)/fractals/julia.c \
              $(SRCS_DIR)/fractals/mandelbrot.c \
              $(SRCS_DIR)/fractals/mandelbox.c \
              $(SRCS_DIR)/fractals/tricorn.c \
              $(SRCS_DIR)/events.c \
              $(SRCS_DIR)/main.c \
              $(SRCS_DIR)/make_engine.c \
              $(SRCS_DIR)/render.c \
              $(SRCS_DIR)/utils.c

# Object files
OBJS        = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Commandes principales
all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)
	@echo "\033[2J\033[1;1H\033[36m"
	@echo " █████╗ ██╗   ██╗██████╗       ██████╗ ██████╗ "
	@echo "██╔══██╗██║   ██║██╔══██╗      ╚════██╗██╔══██╗"
	@echo "██║  ╚═╝██║   ██║██████╦╝       █████╔╝██║  ██║"
	@echo "██║  ██╗██║   ██║██╔══██╗       ╚═══██╗██║  ██║"
	@echo "╚█████╔╝╚██████╔╝██████╦╝      ██████╔╝██████╔╝"
	@echo " ╚════╝  ╚═════╝ ╚═════╝       ╚═════╝ ╚═════╝ "
	@echo "Mon premier RayCaster avec la minilibX\n"

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB) $(LIBFT_LIB) -lXext -lX11 -lm -O3

# Générer les répertoires nécessaires pour les objets
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)/fractals
	$(CC) $(CFLAGS) -c $< -o $@

# Créer les répertoires nécessaires (obj et obj/fractals)
$(OBJS_DIR)/fractals:
	mkdir -p $(OBJS_DIR)/fractals

$(OBJS_DIR):
	@if [ ! -d "$(OBJS_DIR)" ]; then \
		echo "$(BLUE)◇ Creating $(OBJS_DIR):$(NO_COLOR)"; \
		echo "│ mkdir -p $(OBJS_DIR)"; \
		mkdir -p $(OBJS_DIR); \
	fi

$(MLX_LIB): force
	make -C $(MLX_DIR)

$(LIBFT_LIB): force
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

force:
	@true

.PHONY: all clean fclean re
