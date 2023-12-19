/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:03:54 by jonghopa          #+#    #+#             */
/*   Updated: 2023/04/08 18:29:11 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include	"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (new_str == 0)
		return (0);
	i = 0;
	new_str[s1_len + s2_len] = 0;
	while (i < s1_len)
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
		new_str[i++] = s2[j++];
	return (new_str);
}
