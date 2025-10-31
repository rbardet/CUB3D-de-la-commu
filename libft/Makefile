# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 05:59:42 by rbardet-          #+#    #+#              #
#    Updated: 2025/10/11 20:27:26 by rbardet-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CHAR_DIR = src/char
GNL_DIR = src/gnl
INT_DIR = src/int
LIST_DIR = src/list
PRINT_DIR = src/print
PRINTF_DIR = src/printf
STRING_DIR = src/string
TAB_DIR = src/tab
OBJ_DIR = objs

SOURCES = \
${CHAR_DIR}/ft_isalpha.c \
${CHAR_DIR}/ft_isdigit.c \
${CHAR_DIR}/ft_isalnum.c \
${CHAR_DIR}/ft_isascii.c \
${CHAR_DIR}/ft_isprint.c \
${CHAR_DIR}/is_space.c \
${CHAR_DIR}/ft_toupper.c \
${CHAR_DIR}/ft_tolower.c \
${STRING_DIR}/ft_strlen.c \
${STRING_DIR}/ft_memset.c \
${STRING_DIR}/ft_bzero.c \
${STRING_DIR}/ft_memcpy.c \
${STRING_DIR}/ft_memmove.c \
${STRING_DIR}/ft_strlcpy.c \
${STRING_DIR}/ft_strlcat.c \
${STRING_DIR}/ft_strchr.c \
${STRING_DIR}/ft_strrchr.c \
${STRING_DIR}/ft_strncmp.c \
${STRING_DIR}/ft_memchr.c \
${STRING_DIR}/ft_memcmp.c \
${STRING_DIR}/ft_strnstr.c \
${STRING_DIR}/ft_calloc.c \
${STRING_DIR}/ft_strdup.c \
${STRING_DIR}/ft_substr.c \
${STRING_DIR}/ft_strjoin.c \
${STRING_DIR}/ft_strtrim.c \
${STRING_DIR}/ft_strmapi.c \
${STRING_DIR}/ft_striteri.c \
${STRING_DIR}/ft_itoa.c \
${PRINT_DIR}/ft_putchar_fd.c \
${PRINT_DIR}/ft_putstr_fd.c \
${PRINT_DIR}/ft_putendl_fd.c \
${PRINT_DIR}/ft_putnbr_fd.c \
${TAB_DIR}/free_tab.c \
${TAB_DIR}/tab_size.c \
${TAB_DIR}/ft_tabchr.c \
${TAB_DIR}/sort_str_tab.c \
${TAB_DIR}/print_tab.c \
${TAB_DIR}/copy_tab.c \
${TAB_DIR}/tablen.c \
${TAB_DIR}/ft_tabdup.c \
${TAB_DIR}/ft_split.c \
${INT_DIR}/ft_atoi.c \
${PRINTF_DIR}/ft_printf_s.c \
${PRINTF_DIR}/ft_printf_id.c \
${PRINTF_DIR}/ft_printf_p.c \
${PRINTF_DIR}/ft_printf_prc.c \
${PRINTF_DIR}/ft_printf_u.c \
${PRINTF_DIR}/ft_printf_xmin.c \
${PRINTF_DIR}/ft_printf_xmaj.c \
${PRINTF_DIR}/ft_printf_c.c \
${PRINTF_DIR}/ft_printf.c \
${GNL_DIR}/get_next_line_bonus.c \
${LIST_DIR}/ft_lstnew_bonus.c \
${LIST_DIR}/ft_lstadd_front_bonus.c \
${LIST_DIR}/ft_lstsize_bonus.c \
${LIST_DIR}/ft_lstlast_bonus.c \
${LIST_DIR}/ft_lstadd_back_bonus.c \
${LIST_DIR}/ft_lstdelone_bonus.c \
${LIST_DIR}/ft_lstclear_bonus.c \
${LIST_DIR}/ft_lstiter_bonus.c

OBJECTS = $(SOURCES:.c=.o)
OBJECTS := $(patsubst src/%.o, $(OBJ_DIR)/%.o, $(OBJECTS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rsc $@ $^

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
