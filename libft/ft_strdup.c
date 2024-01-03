/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:18:21 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 16:38:44 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

char	*ft_strdup(const char *s1)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!tmp)
		return (NULL);
	ft_memcpy(tmp, s1, ft_strlen(s1) + 1);
	return (tmp);
}
