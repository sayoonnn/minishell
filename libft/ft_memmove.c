/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:59:08 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 15:23:58 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		cnt;
	char		*t_dst;
	const char	*t_src;

	t_dst = (char *)dst;
	t_src = (const char *)src;
	if ((!t_dst && !t_src) || !len)
		return (dst);
	if (dst > src)
	{
		cnt = len;
		while (--cnt > 0)
			*(t_dst + cnt) = *(t_src + cnt);
		*(t_dst + cnt) = *(t_src + cnt);
	}
	else
	{
		cnt = -1;
		while (++cnt < len)
			*(t_dst + cnt) = *(t_src + cnt);
	}
	return (dst);
}
