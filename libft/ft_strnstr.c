/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:39:18 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/06 21:54:16 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	hay_len;
	size_t	cnt;

	if (*needle == 0)
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	if (needle_len > len)
		return (NULL);
	hay_len = ft_strlen(haystack);
	cnt = 0;
	while (cnt + needle_len <= len && cnt + needle_len <= hay_len)
	{
		if (!ft_strncmp(haystack, needle, needle_len))
			return ((char *)haystack);
		cnt++;
		haystack++;
	}
	return (NULL);
}
