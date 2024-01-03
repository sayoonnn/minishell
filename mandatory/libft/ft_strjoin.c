/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:44:28 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/06 15:17:07 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	if (s2 == NULL)
		s2_len = 0;
	else
		s2_len = ft_strlen(s2);
	tmp = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, s1, s1_len);
	if (s2 != NULL)
		ft_memcpy(tmp + s1_len, s2, s2_len);
	*(tmp + s1_len + s2_len) = 0;
	return (tmp);
}
