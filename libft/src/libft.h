/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 05:33:10 by rbardet-          #+#    #+#             */
/*   Updated: 2025/10/11 20:09:14 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>

# define BUFFER_SIZE 100
# define OPEN_MAX 1000

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char				**ft_tabdup(char **tab);
int					ft_tablen(char **tab);
void				printab(char *fmt, char **tab);
int					ft_isspace(char c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(char *s);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
long int			ft_atol(char *nptr);
int					ft_atoi(char *nptr);
char				*ft_strdup(char *s);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, char *src, size_t size);
size_t				ft_strlcat(char *dst, char *src, size_t size);
char				*ft_strchr(char *s, int c);
char				*ft_strrchr(char *s, int c);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
char				*ft_strnstr(char *big, char *little, size_t len);
char				**ft_tabchr(char **tab, int c);
char				**ft_tabtabchr(char **tab, char *c);

void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strtrim(char *s1, char *set);
char				*ft_itoa(int n);
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				**ft_split(char *s, char c);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));

int					ft_printf_c(char c);
int					ft_printf_id(int c);
int					ft_printf_p(unsigned long long a);
int					ft_printf_prc(void);
int					ft_printf_s(char *str);
int					ft_printf_u(unsigned int a);
int					ft_printf_xmin(unsigned int a);
int					ft_printf_xmaj(unsigned int a);
int					ft_printf(char *str, ...);

char				*get_next_line(int fd);
char				**free_tab(char **tab);
int					tab_size(char **tab);
char				**sort_str_tab(char **tab);
void				printab(char *fmt, char **tab);
char				**copy_tab(char **src);


#endif
