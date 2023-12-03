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

t_envnode	*make_envnode(char *key, char *value)
{
	t_envnode	*tmp;

	tmp = malloc(sizeof(t_envnode));
	if (!tmp)
		exit(1);
	tmp->key = ft_strdup(key);
	tmp->value = ft_strdup(value);
	tmp->left = NULL;
	tmp->right = NULL;
	if (!tmp->key || !tmp->value)
		exit(1);
	return (tmp);
}

void	print_envnode(t_envnode *tree)
{
	if (tree == NULL)
		return ;
	print_envnode(tree->left);
	printf("%s=%s\n", tree->key, tree->value);
	print_envnode(tree->right);
}

t_envnode	*add_envnode(t_envnode *tree, t_envnode *newnode)
{
	if (tree == NULL)
		return (newnode);
	if (!ft_strcmp(tree->key, newnode->key))
	{
		free(tree->key);
		free(tree->value);
		tree->key = newnode->key;
		tree->value = newnode->value;
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
	if (ft_strcmp(root->key, key < 0))
		return (find_envnode(root->right, key));
	return (NULL);
}

static void	free_node(t_envnode *node)
{
	free(node->key);
	free(node->value);
	free(node);
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
