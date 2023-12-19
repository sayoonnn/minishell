/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:52:14 by jonghopa          #+#    #+#             */
/*   Updated: 2023/06/29 17:08:16 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

int	ft_atoi(const char *str)
{
	int				sign;
	int				i;
	unsigned long	ret;
	unsigned long	temp;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign *= -1;
	i += (str[i] == '+' || str[i] == '-');
	ret = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = ret * 10 + (str[i] - '0');
		if (temp > (unsigned long) LONG_MAX || ret > temp)
			return (-1 + (sign < 0));
		ret = temp;
		i++;
	}
	return (ret * sign);
}
