/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:18:27 by sayoon            #+#    #+#             */
/*   Updated: 2023/11/29 17:18:28 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE 1

#include "libft/libft.h"

typedef struct s_tree_node
{
	int 			type;
	// 정보
	struct s_tree *left;
	struct s_tree *right;
}			t_tree_node;

#endif
