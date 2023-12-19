/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:32:02 by jonghopa          #+#    #+#             */
/*   Updated: 2023/04/03 19:17:02 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (fd == -1)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	return ;
}
