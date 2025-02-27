/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:28:41 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/21 23:16:13 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstadd_back(t_list *lst, t_node *new)
{
	t_node	*tmp;

	if (lst->tail == NULL)
	{
		lst->head = new;
		lst->tail = new;
		return ;
	}
	tmp = lst->tail;
	tmp->next = new;
	lst->tail = new;
}
