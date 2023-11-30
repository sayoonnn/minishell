/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:01:14 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/11 14:01:15 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int	gnl_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

void	*gnl_memcpy(void *dst, void *src, int n)
{
	int	cnt;

	if (!dst && !src)
		return (NULL);
	cnt = 0;
	while (cnt < n)
	{
		*((char *)dst + cnt) = *((char *)src + cnt);
		cnt ++;
	}
	*((char *)dst + n) = 0;
	return (dst);
}

char	*gnl_strjoin(char *s1, char *s2, int s2_len)
{
	char	*tmp;
	int		s1_len;

	if (!s1)
		s1 = "";
	s1_len = gnl_strlen(s1);
	tmp = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	gnl_memcpy(tmp, s1, s1_len);
	gnl_memcpy(tmp + s1_len, s2, s2_len);
	return (tmp);
}

char	*gnl_strdup(char *s1, int len)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	gnl_memcpy(tmp, s1, len);
	return (tmp);
}

char	*gnl_memchr(char *s, int c, int n)
{
	int	cnt;

	cnt = 0;
	while (cnt < n)
	{
		if (*(s + cnt) == (char)c)
			return (s + cnt);
		cnt++;
	}
	return (NULL);
}
