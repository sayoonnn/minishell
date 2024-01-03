/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:15:57 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/06 17:11:07 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rev;
	int		st;
	int		end;

	st = 0;
	while (ft_strchr(set, *(s1 + st)) && *(s1 + st))
		st++;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, *(s1 + end)) && end > 0)
		end--;
	if (end == 0)
		return (ft_strdup(""));
	rev = (char *)malloc(sizeof(char) * (end - st + 2));
	if (!rev)
		return (NULL);
	ft_memcpy(rev, s1 + st, end - st + 1);
	rev[end - st + 1] = 0;
	return (rev);
}
