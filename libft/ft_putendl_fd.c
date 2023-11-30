/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:04:09 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 14:56:45 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	ft_putendl_fd(char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) < 0)
		exit(1);
	if (write(fd, "\n", 1) < 0)
		exit(1);
	return ;
}
