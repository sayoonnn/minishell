/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:11:42 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 16:14:24 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getlen(int n)
{
	int	len;

	if (n == 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*rev;
	int		sign;
	int		len;

	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		sign = 1;
	}
	len = ft_getlen(n);
	rev = (char *)ft_calloc(sizeof(char), (len + sign + 1));
	if (!rev)
		return (NULL);
	if (sign)
		*rev = '-';
	while (--len >= 0)
	{
		*(rev + len + sign) = n % 10 + '0';
		n /= 10;
	}
	return (rev);
}
