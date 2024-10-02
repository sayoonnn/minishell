/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:25:15 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 11:10:03 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include <stdlib.h>

typedef struct s_node
{
	char			*content;
	struct s_node	*next;
}				t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
}				t_list;

t_list	*ft_lstcreate(void);
t_node	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list *lst, t_node *new);
int		ft_lstsize(t_list *lst);
t_node	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_node *argv);
void	ft_lstclear(t_list *lst);

#endif