/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:53:51 by jonghopa          #+#    #+#             */
/*   Updated: 2023/10/03 22:13:34 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char)c;
	while (s[i] != '\0' && s[i] != ch)
		i++;
	if (ch != '\0' && s[i] == '\0')
		return (0);
	return ((char *)(s + i));
}
