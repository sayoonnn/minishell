/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:12:11 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/07 17:00:06 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	void	*tcont;
	t_list	*rev;

	rev = NULL;
	while (lst != NULL)
	{
		tcont = f(lst->content);
		tmp = ft_lstnew(tcont);
		if (!tmp)
		{
			del(tcont);
			ft_lstclear(&rev, del);
			return (NULL);
		}
		ft_lstadd_back(&rev, tmp);
		lst = lst->next;
	}
	return (rev);
}
