/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_push_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:46:07 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 16:35:41 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

int	deque_push_back(t_deque *deque, int type, char *content)
{
	t_deque_node	*new;
	t_deque_node	*tmp;

	if (deque == NULL || content == NULL)
		return (1);
	new = deque_create_node(type, content);
	if (new == NULL)
		return (1);
	if (deque->front == NULL && deque->back == NULL)
	{
		deque->front = new;
		deque->back = new;
	}
	else
	{
		tmp = deque->back;
		new->left = tmp;
		tmp->right = new;
		deque->back = new;
	}
	return (0);
}
