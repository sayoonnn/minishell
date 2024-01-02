/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:10:01 by jonghopa          #+#    #+#             */
/*   Updated: 2023/09/26 18:54:17 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

int	deque_size(t_deque *deque)
{
	int				size;
	t_deque_node	*ptr;

	size = 0;
	ptr = deque->front;
	while (ptr != NULL)
	{
		size += 1;
		ptr = ptr->right;
	}
	return (size);
}
