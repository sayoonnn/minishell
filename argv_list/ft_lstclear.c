/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:29:04 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 23:02:45 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_list.h"

void	ft_lstclear(t_list *lst, int status)
{
	t_argv	*tmp;

	while (lst->head != NULL)
	{
		tmp = lst->head;
		lst->head = lst->head->next;
		tmp->next = NULL;
		ft_lstdelone(tmp, status);
	}
	lst->tail = NULL;
	return ;
}
