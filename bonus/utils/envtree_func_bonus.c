/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtree_func_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:37:24 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 13:23:10 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "env_tree_bonus.h"

t_envnode	*make_envnode(char *key, char *value)
{
	t_envnode	*tmp;
	char		*t;

	tmp = malloc(sizeof(t_envnode));
	if (!tmp)
		exit(1);
	tmp->key = ft_strdup(key);
	if (value != NULL)
		tmp->value = ft_strdup(value);
	else
		tmp->value = NULL;
	t = ft_strjoin(tmp->key, "=");
	if (value != NULL)
	{
		tmp->forarr = ft_strjoin(t, tmp->value);
		free(t);
	}
	else
		tmp->forarr = t;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

void	add_env(t_envtree *env, t_envnode *newnode)
{
	if (!find_envnode(env->root, newnode->key))
		env->num_nodes++;
	env->root = add_envnode(env->root, newnode);
}

t_envnode	*add_envnode(t_envnode *tree, t_envnode *newnode)
{
	if (tree == NULL)
		return (newnode);
	if (!ft_strcmp(tree->key, newnode->key))
	{
		free(tree->key);
		free(tree->value);
		free(tree->forarr);
		tree->key = newnode->key;
		tree->value = newnode->value;
		tree->forarr = newnode->forarr;
		free(newnode);
		return (tree);
	}
	if (ft_strcmp(tree->key, newnode->key) > 0)
		tree->left = add_envnode(tree->left, newnode);
	else
		tree->right = add_envnode(tree->right, newnode);
	return (tree);
}

t_envnode	*find_envnode(t_envnode *root, char *key)
{
	if (root == NULL)
		return (NULL);
	if (!ft_strcmp(root->key, key))
		return (root);
	if (ft_strcmp(root->key, key) > 0)
		return (find_envnode(root->left, key));
	if (ft_strcmp(root->key, key) < 0)
		return (find_envnode(root->right, key));
	return (root);
}

void	clear_node(t_envnode *env)
{
	if (env == NULL)
		return ;
	clear_node(env->left);
	clear_node(env->right);
	free_node(env);
}
