/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tree_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:37:24 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 19:37:25 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_tree.h"

static void	free_node(t_envnode *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static t_envnode	*delete_leafnode(t_envnode *env)
{
	t_envnode	*tmp;

	if (env->right == NULL && env->left == NULL)
	{
		free_node(env);
		return (NULL);
	}
	if (env->right != NULL && env->left == NULL)
	{
		tmp = env->right;
		free_node(env);
		return (tmp);
	}
	if (env->right == NULL && env->left != NULL)
	{
		tmp = env->left;
		free_node(env);
		return (tmp);
	}
	return (NULL);
}

t_envnode	*delete_envnode(t_envnode *env, char *str)
{
	t_envnode	*tmp;

	if (env == NULL)
		return (NULL);
	if (ft_strcmp(env->key, str) > 0)
		env->left = delete_envnode(env->left, str);
	else if (ft_strcmp(env->key, str) < 0)
		env->right = delete_envnode(env->right, str);
	else
	{
		if ((env->right == NULL && env->left == NULL) \
		|| env->right != NULL || env->left != NULL)
			return (delete_leafnode(env));
		tmp = env->right;
		while (tmp->left != NULL)
			tmp = tmp->left;
		free(env->key);
		free(env->value);
		env->key = ft_strdup(tmp->key);
		env->value = ft_strdup(tmp->value);
		env->right = delete_envnode(env->right, env->key);
	}
	return (env);
}

void	clear_node(t_envnode *env)
{
	if (env == NULL)
		return ;
	clear_node(env->left);
	clear_node(env->right);
	free_node(env);
}
