/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:30:12 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/21 23:16:39 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

int	ft_lstsize(t_list *lst)
{
	t_node	*tmp;
	int		len;

	len = 0;
	tmp = lst->head;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
