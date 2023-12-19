/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:18:55 by jonghopa          #+#    #+#             */
/*   Updated: 2023/10/04 16:04:53 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	ch;

	i = ft_strlen(s);
	ch = (unsigned char)c;
	while (i > 0 && s[i] != ch)
		i--;
	if (i == 0 && s[i] != ch)
		return (NULL);
	return ((char *)(s + i));
}
