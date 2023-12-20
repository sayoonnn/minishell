/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:31:11 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/13 20:59:38 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_list.h"

t_argv	*ft_lstlast(t_list *lst)
{
	t_argv	*tmp;

	if (lst->tail == NULL)
		return (NULL);
	tmp = lst->tail;
	return (tmp);
}
