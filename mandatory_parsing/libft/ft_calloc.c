/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:51:53 by jonghopa          #+#    #+#             */
/*   Updated: 2023/06/29 16:06:48 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t			i;
	unsigned char	*zero;

	i = 0;
	zero = (unsigned char *)malloc(num * size);
	if (zero == 0)
		return (0);
	while (i < num * size)
		zero[i++] = 0;
	return (zero);
}
