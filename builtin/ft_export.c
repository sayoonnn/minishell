/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:21:01 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 20:21:02 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_tree.h"

static void	print_envnode(t_envnode *tree)
{
	if (tree == NULL)
		return ;
	print_envnode(tree->left);
	printf("declare -x %s=\"%s\"\n", tree->key, tree->value);
	print_envnode(tree->right);
}

static void	add_value(t_envtree *env, char *key, char *value)
{
	t_envnode	*node;
	char		*tmp;

	node = find_envnode(env->root, key);
	if (!node)
		add_env(env, make_envnode(key, value));
	else
	{
		tmp = node->value;
		node->value = ft_strjoin(node->value, value);
		free(tmp);
		tmp = node->forarr;
		node->forarr = ft_strjoin(node->forarr, value);
		free(tmp);
	}
}

// 인자가 여러개 들어올 경우 =이 붙은 것만 체크하면 됨

int	ft_export(char *arg[], t_envtree *env)
{
	char	*key;
	char	*value;

	if (arg[1] == NULL)
	{
		print_envnode(env->root);
		return (0);
	}
	key = arg[1];
	value = ft_strchr(arg[1], '=');
	if (!value)
	{
		add_env(env, make_envnode(key, ""));
		return (0);
	}
	if (*(ft_strchr(arg[1], '=') - 1) == '+')
	{
		*ft_strchr(arg[1], '+') = 0;
		add_value(env, key, value + 1);
	}
	else
	{
		*ft_strchr(arg[1], '=') = 0;
		add_env(env, make_envnode(key, value + 1));
	}
	return (0);
}
