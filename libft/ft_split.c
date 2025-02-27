/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:58:03 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 21:13:30 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_getrow(char *s, char c)
{
	int	row;

	row = 0;
	while (*s)
	{
		if (*s != c && *(s + 1) == c)
			row++;
		s++;
	}
	if (*(s - 1) != c)
		row++;
	return (row);
}

static int	ft_substrlen(char *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s != 0)
	{
		len++;
		s++;
	}
	if (!*s && *(s - 1) != c)
		len++;
	return (len);
}

static void	*ft_freeall(char **arr, int n)
{
	int	cnt;

	cnt = 0;
	while (cnt < n)
	{
		free(arr[cnt]);
		cnt++;
	}
	free(arr);
	return (NULL);
}

static char	**ft_emptyc(char const *s)
{
	char	**tmp;

	if (*s == 0)
	{
		tmp = (char **)malloc(sizeof(char *) * 1);
		if (!tmp)
			return (NULL);
		tmp[0] = NULL;
		return (tmp);
	}
	else
	{
		tmp = (char **)malloc(sizeof(char *) * 2);
		if (!tmp)
			return (NULL);
		tmp[0] = ft_strdup(s);
		if (!tmp[0])
		{
			free(tmp);
			return (NULL);
		}
		tmp[1] = NULL;
		return (tmp);
	}
}

char	**ft_oldsplit(char const *s, char c)
{
	int		row;
	int		cnt;
	int		idx;
	char	**tmp;

	if (c == 0 || *s == 0)
		return (ft_emptyc(s));
	row = ft_getrow((char *)s, c);
	tmp = (char **)malloc(sizeof(char *) * (row + 1));
	if (!tmp)
		return (NULL);
	tmp[row] = NULL;
	cnt = 0;
	idx = 0;
	while (cnt < row)
	{
		while (*(s + idx) == c)
			idx++;
		tmp[cnt] = ft_substr(s, idx, ft_substrlen((char *)(s + idx), c));
		if (!tmp[cnt])
			return (ft_freeall(tmp, cnt));
		idx += ft_substrlen((char *)(s + idx), c);
		cnt++;
	}
	return (tmp);
}
