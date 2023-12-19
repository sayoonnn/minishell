/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 00:00:39 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/09 20:32:41 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	hs_idx;
	size_t	nd_idx;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	hs_idx = 0;
	while (haystack[hs_idx] != '\0' && hs_idx < len)
	{
		nd_idx = 0;
		while ((haystack[hs_idx + nd_idx] == needle[nd_idx])
			&& (hs_idx + nd_idx) < len
			&& haystack[hs_idx + nd_idx] != '\0' && needle[nd_idx] != '\0')
			nd_idx++;
		if (nd_idx == needle_len)
			return ((char *)(haystack + hs_idx));
		hs_idx++;
	}
	return (NULL);
}
