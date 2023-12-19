/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_pop_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:46:02 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/09 16:13:03 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

void	deque_pop_back(t_deque *deque)
{
	t_deque_node	*tmp;

	if (deque_empty(deque))
		return ;
	tmp = deque->back;
	deque->back = tmp->left;
	if (deque->back == NULL)
		deque->front = NULL;
	else
		deque->back->right = NULL;
	tmp->left = NULL;
	free(tmp->content);
	free(tmp);
}
