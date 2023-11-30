/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:29:23 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 15:29:45 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	tmp;
	int			sign;
	char		*s;

	s = (char *)str;
	sign = 1;
	tmp = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	if (!ft_isdigit(*s))
		return (0);
	while (ft_isdigit(*s))
	{
		tmp *= 10;
		tmp += *s - '0';
		s++;
	}
	return ((int)(tmp * sign));
}
