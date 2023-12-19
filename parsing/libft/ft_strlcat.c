/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:42:17 by jonghopa          #+#    #+#             */
/*   Updated: 2023/04/08 18:25:41 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t s)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dest_len = 0;
	src_len = 0;
	while (dst[dest_len] != '\0')
		dest_len++;
	while (src[src_len] != '\0')
		src_len++;
	if (s == 0 || dest_len >= s)
		return (src_len + s);
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && j < s - dest_len - 1)
	{
		dst[i] = src[j++];
		i++;
	}
	dst[i] = '\0';
	return (src_len + dest_len);
}
