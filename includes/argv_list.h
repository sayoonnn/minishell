/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_list.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:25:15 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 20:55:26 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_LIST_H
# define ARGV_LIST_H
# include <stdlib.h>

typedef struct s_argv
{
	char			*content;
	struct s_argv	*next;
}				t_argv;

typedef struct s_list
{
	t_argv	*head;
	t_argv	*tail;
}				t_list;

t_list	*ft_lstcreate(void);
t_argv	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list *lst, t_argv *new);
int		ft_lstsize(t_list *lst);
t_argv	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_argv *argv, int status);
void	ft_lstclear(t_list *lst, int status);
char	**ft_split(char const *s);

#endif
