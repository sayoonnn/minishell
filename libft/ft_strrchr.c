/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:57:02 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/05 16:46:36 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		idx;

	idx = ft_strlen(s);
	while (idx >= 0)
	{
		if (*(s + idx) == (char)c)
			return ((char *)s + idx);
		idx--;
	}
	return (NULL);
}
