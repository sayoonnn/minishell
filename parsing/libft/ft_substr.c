/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 02:26:43 by jonghopa          #+#    #+#             */
/*   Updated: 2023/10/04 11:48:41 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	sub_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	sub_len = 0;
	if (s_len > start)
	{
		if (len <= s_len - start)
			sub_len = len;
		else
			sub_len = s_len - start;
	}
	sub = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (start < s_len && i < len)
		sub[i++] = s[start++];
	sub[i] = 0;
	return (sub);
}
