/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 00:28:09 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 16:27:05 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nxt;

	if (*lst == NULL)
		return ;
	nxt = (*lst)->next;
	while (*lst != NULL)
	{
		ft_lstdelone(*lst, del);
		*lst = nxt;
		if (nxt != NULL)
			nxt = nxt->next;
	}
	return ;
}
