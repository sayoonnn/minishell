/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:49:10 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 15:23:58 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	cnt;

	if (dstsize == 0)
		return (ft_strlen(src));
	cnt = 0;
	while (*(src + cnt) && cnt < dstsize - 1)
	{
		*(dst + cnt) = *(src + cnt);
		cnt++;
	}
	*(dst + cnt) = 0;
	return (ft_strlen(src));
}
