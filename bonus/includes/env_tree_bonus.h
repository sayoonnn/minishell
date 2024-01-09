/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tree_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:33:07 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:42:09 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TREE_BONUS_H
# define ENV_TREE_BONUS_H

# include <stdlib.h>
# include <stdio.h>

t_envnode	*make_envnode(char *key, char *value);
t_envnode	*add_envnode(t_envnode *tree, t_envnode *newnode);
t_envnode	*delete_envnode(t_envnode *env, char *str);
t_envnode	*find_envnode(t_envnode *root, char *key);
void		add_env(t_envtree *env, t_envnode *newnode);
void		clear_node(t_envnode *env);
void		free_node(t_envnode *node);

#endif
