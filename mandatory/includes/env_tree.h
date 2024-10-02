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
# include "types.h"

t_envnode	*make_envnode(char *key, char *value);
t_envnode	*add_envnode(t_envnode *tree, t_envnode *newnode);
t_envnode	*delete_envnode(t_envnode *env, char *str);
t_envnode	*find_envnode(t_envnode *root, char *key);
void		add_env(t_envtree *env, t_envnode *newnode);
void		clear_node(t_envnode *env);
void		free_node(t_envnode *node);

#endif
