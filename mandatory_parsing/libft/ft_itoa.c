/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:19:46 by jonghopa          #+#    #+#             */
/*   Updated: 2023/04/07 21:09:10 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

int	alloc_space(long num)
{
	int	cnt;

	cnt = 0;
	if (num <= 0)
	{
		num *= -1;
		cnt++;
	}
	while (num != 0)
	{
		num /= 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	char	*itoa_str;
	long	l_num;
	int		space;
	int		i;

	l_num = (long)n;
	space = alloc_space(l_num);
	itoa_str = (char *)malloc(sizeof(char) * (space + 1));
	if (itoa_str == 0)
		return (0);
	itoa_str[space--] = '\0';
	i = 0;
	if (l_num < 0)
	{
		itoa_str[0] = '-';
		l_num *= -1;
		i = 1;
	}
	while (space >= i)
	{
		itoa_str[space--] = l_num % 10 + '0';
		l_num /= 10;
	}
	return (itoa_str);
}
