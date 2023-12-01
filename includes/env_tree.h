/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:33:07 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 19:33:09 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TREE_H
# define ENV_TREE_H

# include <stdlib.h>
# include <stdio.h>

typedef struct	s_envnode
{
	char				*key;
	char				*value;
	struct s_envnode	*left;
	struct s_envnode	*right;
}				t_envnode;

t_envnode	*make_envnode(char *key, char *value);
t_envnode	*add_envnode(t_envnode *tree, t_envnode *newnode);
t_envnode	*delete_envnode(t_envnode *env, char *str);
void		print_envnode(t_envnode *tree);

#endif
