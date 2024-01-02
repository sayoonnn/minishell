/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:03:29 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/29 15:03:31 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_hex(int fd, unsigned int num, int *cnt, char *hex)
{
	static int	w_error;

	if (num / 16 > 0)
		ft_print_hex(fd, num / 16, cnt, hex);
	if (w_error < 0)
		return (FAIL);
	num %= 16;
	w_error = write(fd, &hex[num], 1);
	if (w_error < 0)
		return (FAIL);
	(*cnt)++;
	return (*cnt);
}

int	ft_print_x(int fd, va_list ap, char is_upper)
{
	char			*hex;
	int				cnt;
	unsigned int	num;

	if (is_upper == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	cnt = 0;
	num = va_arg(ap, unsigned int);
	return (ft_print_hex(fd, num, &cnt, hex));
}
