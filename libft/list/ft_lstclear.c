/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:29:04 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 11:09:45 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstclear(t_list *lst)
{
	t_node	*tmp;

	while (lst->head != NULL)
	{
		tmp = lst->head;
		lst->head = lst->head->next;
		tmp->next = NULL;
		ft_lstdelone(tmp);
	}
	lst->tail = NULL;
	return ;
}
