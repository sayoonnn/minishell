/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:43:35 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 15:26:58 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	cnt;

	cnt = 0;
	if (!dst && !src)
		return (NULL);
	while (cnt < n)
	{
		*((char *)dst + cnt) = *((char *)src + cnt);
		cnt ++;
	}
	return (dst);
}
