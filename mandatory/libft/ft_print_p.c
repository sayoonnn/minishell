/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:58:05 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/26 19:58:07 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static int	ft_print_addr(int fd, uintptr_t num, int *cnt)
{
	static int	w_error;

	if (num / 16 > 0)
		ft_print_addr(fd, num / 16, cnt);
	w_error = write(fd, &"0123456789abcdef"[num % 16], 1);
	if (w_error < 0)
		return (FAIL);
	(*cnt)++;
	return (*cnt);
}

int	ft_print_p(int fd, va_list ap)
{
	int			written_bytes;
	int			cnt;
	uintptr_t	addr;

	cnt = 0;
	written_bytes = 0;
	addr = va_arg(ap, uintptr_t);
	written_bytes += write(fd, "0x", 2);
	if (written_bytes < 0)
		return (FAIL);
	written_bytes += ft_print_addr(fd, addr, &cnt);
	if (written_bytes < 0)
		return (FAIL);
	return (written_bytes);
}
