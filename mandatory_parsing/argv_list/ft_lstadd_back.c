/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:28:41 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 23:24:56 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_list.h"
#include <stdio.h>

void	ft_lstadd_back(t_list *lst, t_argv *new)
{
	t_argv	*tmp;

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
