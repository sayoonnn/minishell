/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:27:43 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/05 15:45:31 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				cnt;
	const unsigned char	*t_s1;
	const unsigned char	*t_s2;

	cnt = 0;
	t_s1 = s1;
	t_s2 = s2;
	if (n == 0)
		return (0);
	while (cnt < n)
	{
		if (*(t_s1 + cnt) != *(t_s2 + cnt))
			return (*(t_s1 + cnt) - *(t_s2 + cnt));
		cnt++;
	}
	return (0);
}
