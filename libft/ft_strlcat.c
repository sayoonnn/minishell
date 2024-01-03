/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:12:27 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 15:23:58 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	cnt;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	cnt = 0;
	while (*(src + cnt) && dst_len + cnt < dstsize - 1)
	{
		*(dst + dst_len + cnt) = *(src + cnt);
		cnt++;
	}
	*(dst + dst_len + cnt) = 0;
	return (src_len + dst_len);
}
