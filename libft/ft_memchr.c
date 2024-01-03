/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:03:55 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/05 15:32:31 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			cnt;
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	cnt = 0;
	while (cnt < n)
	{
		if (*(tmp + cnt) == (unsigned char)c)
			return ((void *)(tmp + cnt));
		cnt++;
	}
	return (NULL);
}
