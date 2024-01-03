/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_diu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:50:19 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/26 20:50:21 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_int(int fd, int num, int *cnt)
{
	static int	w_error;

	if (num / 10 > 0 || num / 10 < 0)
		ft_print_int(fd, num / 10, cnt);
	if (w_error < 0)
		return (FAIL);
	if (num < 0)
		num = (num % 10) * -1;
	else
		num %= 10;
	w_error = write(fd, &"0123456789"[num], 1);
	if (w_error < 0)
		return (FAIL);
	(*cnt)++;
	return (*cnt);
}

int	ft_print_di(int fd, va_list ap)
{
	int	num;
	int	cnt;
	int	written_bytes;

	cnt = 0;
	written_bytes = 0;
	num = va_arg(ap, int);
	if (num < 0)
		written_bytes = write(fd, "-", 1);
	if (written_bytes < 0)
		return (FAIL);
	written_bytes += ft_print_int(fd, num, &cnt);
	return (written_bytes);
}

static int	ft_print_uint(int fd, unsigned int num, int *cnt)
{
	static int	w_error;

	if (num / 10 > 0)
		ft_print_int(fd, num / 10, cnt);
	if (w_error < 0)
		return (FAIL);
	num %= 10;
	w_error = write(fd, &"0123456789"[num], 1);
	if (w_error < 0)
		return (FAIL);
	(*cnt)++;
	return (*cnt);
}

int	ft_print_u(int fd, va_list ap)
{
	unsigned int	num;
	int				cnt;

	cnt = 0;
	num = va_arg(ap, unsigned int);
	return (ft_print_uint(fd, num, &cnt));
}
