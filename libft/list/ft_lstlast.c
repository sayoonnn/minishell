/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:31:11 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/21 23:16:30 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_node	*ft_lstlast(t_list *lst)
{
	t_node	*tmp;

	if (lst->tail == NULL)
		return (NULL);
	tmp = lst->tail;
	return (tmp);
}
