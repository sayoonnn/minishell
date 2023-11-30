/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:00:10 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/05 16:06:53 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			cnt;
	unsigned char	*t_s1;
	unsigned char	*t_s2;

	t_s1 = (unsigned char *)s1;
	t_s2 = (unsigned char *)s2;
	cnt = 0;
	if (n == 0)
		return (0);
	while (*(t_s1 + cnt) && *(t_s2 + cnt))
	{
		if (cnt == n - 1)
			break ;
		if (*(t_s1 + cnt) != *(t_s2 + cnt))
			break ;
		cnt++;
	}
	return ((int)(*(t_s1 + cnt) - *(t_s2 + cnt)));
}
