/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:32:07 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/26 18:32:09 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_c(int fd, va_list ap)
{
	char	tmp;

	tmp = va_arg(ap, int);
	return (write(fd, &tmp, 1));
}

int	ft_print_s(int fd, va_list ap)
{
	char	*tmp;

	tmp = va_arg(ap, char *);
	if (!tmp)
		return (write(fd, "(null)", 6));
	return (write(fd, tmp, ft_strlen(tmp)));
}

int	ft_print_percent(int fd)
{
	return (write(fd, "%", 1));
}
