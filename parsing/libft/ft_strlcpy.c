/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:52:52 by jonghopa          #+#    #+#             */
/*   Updated: 2023/04/08 18:14:35 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t s)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dst == 0 || src == 0)
		return (0);
	i = 0;
	while (src[i] != '\0' && i + 1 < s)
	{
		dst[i] = src[i];
		i++;
	}
	if (s > 0)
		dst[i] = '\0';
	return (src_len);
}
