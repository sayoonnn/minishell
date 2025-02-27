/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:51:29 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 16:23:21 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

# define FAIL -1

typedef struct s_deque_node
{
	int					token_type;
	char				*content;
	struct s_deque_node	*left;
	struct s_deque_node	*right;
}			t_deque_node;

typedef struct s_deque
{
	t_deque_node	*front;
	t_deque_node	*back;
}			t_deque;

typedef struct s_node
{
	char			*content;
	struct s_node	*next;
}				t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
}				t_list;

void			ft_bzero(void *s, size_t n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *s1, const char *n, size_t len);
char			*ft_strnstr(const char *h, const char *needle, size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_atoi(const char *str);
char			*ft_strdup(const char *s1);
void			*ft_calloc(size_t count, size_t size);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_itoa(int n);
char			**ft_oldsplit(char const *s, char c);

// deque
t_deque			*deque_create(void);
t_deque_node	*deque_create_node(int type, char *content);
int				deque_push_front(t_deque *deque, int type, char *content);
int				deque_push_back(t_deque *deque, int type, char *content);
int				deque_front(t_deque *deque);
int				deque_back(t_deque *deque);
void			deque_pop_front(t_deque *deque);
void			deque_pop_back(t_deque *deque);
int				deque_empty(t_deque *deque);
int				deque_size(t_deque *deque);
void			deque_clear(t_deque *deque);

// list
t_list			*ft_lstcreate(void);
t_node			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list *lst, t_node *new);
int				ft_lstsize(t_list *lst);
t_node			*ft_lstlast(t_list *lst);
void			ft_lstdelone(t_node *argv);
void			ft_lstclear(t_list *lst);
char			**ft_split(char const *s);

// printf
int				ft_printf(int fd, const char *str, ...);
int				ft_doprnt(int fd, va_list ap, const char *str);
char			*ft_strchr(const char *s, int c);
int				ft_print_percent(int fd);
void			ft_init_func(int (*print_func[9]));
int				ft_chk_and_print(int fd, const char *tok, va_list ap);
int				ft_doprnt(int fd, va_list ap, const char *str);
size_t			ft_strlen(const char *s);
int				ft_print_c(int fd, va_list ap);
int				ft_print_s(int fd, va_list ap);
int				ft_print_p(int fd, va_list ap);
int				ft_print_di(int fd, va_list ap);
int				ft_print_u(int fd, va_list ap);
int				ft_print_x(int fd, va_list ap, char is_upper);

#endif
