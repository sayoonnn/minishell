/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:02:24 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/24 16:02:26 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(int fd, const char *str, ...)
{
	va_list	ap;
	int		return_value;

	va_start(ap, str);
	return_value = ft_doprnt(fd, ap, str);
	va_end(ap);
	return (return_value);
}

int	ft_doprnt(int fd, va_list ap, const char *str)
{
	const char	*prev;
	const char	*tok;
	int			ret_val;
	int			byte_written;

	ret_val = 0;
	prev = str;
	tok = ft_strchr(str, '%');
	while (tok)
	{
		byte_written = write(fd, prev, tok - prev);
		if (byte_written < 0)
			return (FAIL);
		ret_val += byte_written;
		byte_written = ft_chk_and_print(fd, tok, ap);
		if (byte_written < 0)
			return (FAIL);
		ret_val += byte_written;
		prev = tok + 2;
		tok = ft_strchr(prev, '%');
	}
	byte_written = write(fd, prev, ft_strlen(prev));
	if (byte_written < 0)
		return (FAIL);
	return (ret_val + byte_written);
}

int	ft_chk_and_print(int fd, const char *tok, va_list ap)
{
	char		*tmp;

	tmp = ft_strchr("cspdiuxX%", *(tok + 1));
	if (!tmp)
		return (FAIL);
	if (*tmp == '%')
		return (ft_print_percent(fd));
	if (*tmp == 'c')
		return (ft_print_c(fd, ap));
	if (*tmp == 's')
		return (ft_print_s(fd, ap));
	if (*tmp == 'p')
		return (ft_print_p(fd, ap));
	if (*tmp == 'd' || *tmp == 'i')
		return (ft_print_di(fd, ap));
	if (*tmp == 'u')
		return (ft_print_u(fd, ap));
	if (*tmp == 'x' || *tmp == 'X')
		return (ft_print_x(fd, ap, *tmp));
	return (FAIL);
}
