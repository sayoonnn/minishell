/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:30:00 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/13 20:36:02 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_list.h"

t_argv	*ft_lstnew(void *content)
{
	t_argv	*new;

	new = (t_argv *)malloc(sizeof(t_argv));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
