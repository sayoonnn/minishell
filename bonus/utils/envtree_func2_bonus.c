/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtree_func2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:37:24 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 13:23:05 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	free_node(t_envnode *node)
{
	free(node->key);
	free(node->value);
	free(node->forarr);
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

static void	make_forarr(t_envnode *env, char *key, char *value)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(key, "=");
	ret = ft_strjoin(tmp, value);
	free(tmp);
	free(env->forarr);
	env->forarr = ret;
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
		|| (env->right != NULL && env->left == NULL) \
		|| (env->left != NULL && env->right == NULL))
			return (delete_leafnode(env));
		tmp = env->right;
		while (tmp->left != NULL)
			tmp = tmp->left;
		free(env->key);
		free(env->value);
		env->key = ft_strdup(tmp->key);
		env->value = ft_strdup(tmp->value);
		make_forarr(env, env->key, env->value);
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
