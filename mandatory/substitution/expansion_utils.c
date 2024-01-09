/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:22:34 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 21:22:36 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "substitution.h"

int	is_there_white(char *str)
{
	while (*str)
	{
		if (is_white(*str))
			return (true);
		str++;
	}
	return (false);
}

int	get_sublen(char *str, char cur)
{
	int	size;

	size = 0;
	while (*str)
	{
		if (*str == cur && is_quote(cur))
			break ;
		else if (!is_quote(cur) && is_quote(*str))
			break ;
		str++;
		size++;
	}
	return (size);
}

void	tokenize_and_add(t_deque *tmp, char *str)
{
	int		start;
	int		len;
	char	*sub_str;

	start = 0;
	while (str[start])
	{
		if (str[start] == '$' && is_quote(str[start + 1]))
		{
			start++;
			continue ;
		}
		len = get_sublen(&str[start + is_quote(*(str + start))], str[start]);
		if (is_quote(str[start]))
			len += 2;
		sub_str = ft_substr(str, start, len);
		if (is_quote(str[start]))
			deque_push_back(tmp, QUOTE, sub_str);
		else
			deque_push_back(tmp, WORD, sub_str);
		start += len;
	}
}

void	sum_lst(t_list *dst, t_list *src)
{
	if (src->head == NULL && src->tail == NULL)
		return ;
	ft_lstadd_back(dst, src->head);
	while (dst->tail->next != NULL)
		dst->tail = dst->tail->next;
}
