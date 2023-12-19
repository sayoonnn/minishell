/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:30:12 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/13 20:58:15 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_list.h"

int	ft_lstsize(t_list *lst)
{
	t_argv	*tmp;
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
