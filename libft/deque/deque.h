/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:31:00 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/17 15:49:04 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_H
# define DEQUE_H

# include <stdlib.h>

typedef struct s_deque_node
{
	int					token_type;
	char				*content;
	struct s_deque_node	*left;
	struct s_deque_node	*right;
}			t_deque_node;

typedef struct s_deque
{
	t_deque_node	*front;
	t_deque_node	*back;
}			t_deque;

t_deque			*deque_create(void);
t_deque_node	*deque_create_node(int type, char *content);
int				deque_push_front(t_deque *deque, int type, char *content);
int				deque_push_back(t_deque *deque, int type, char *content);
int				deque_front(t_deque *deque);
int				deque_back(t_deque *deque);
void			deque_pop_front(t_deque *deque);
void			deque_pop_back(t_deque *deque);
int				deque_empty(t_deque *deque);
int				deque_size(t_deque *deque);
void			deque_clear(t_deque *deque);

#endif