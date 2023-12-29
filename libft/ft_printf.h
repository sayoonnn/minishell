/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:20:36 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/24 17:20:37 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdarg.h>
# include <unistd.h>
# define FAIL -1

int		ft_printf(int fd, const char *str, ...);
int		ft_doprnt(int fd, va_list ap, const char *str);
char	*ft_strchr(const char *s, int c);
int		ft_print_percent(int fd);
void	ft_init_func(int (*print_func[9]));
int		ft_chk_and_print(int fd, const char *tok, va_list ap);
int		ft_doprnt(int fd, va_list ap, const char *str);
size_t	ft_strlen(const char *s);
int		ft_print_c(int fd, va_list ap);
int		ft_print_s(int fd, va_list ap);
int		ft_print_p(int fd, va_list ap);
int		ft_print_di(int fd, va_list ap);
int		ft_print_u(int fd, va_list ap);
int		ft_print_x(int fd, va_list ap, char is_upper);

#endif
