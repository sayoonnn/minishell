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
	printf("declare - x %s=\"%s\"\n", tree->key, tree->value);
	print_envnode(tree->right);
}

static void	add_value(t_envnode *env, char *key, char *value)
{
	t_envnode	*node;
	char		*tmp;

	node = find_envnode(env, key);
	if (!node)
		add_envnode(env, make_envnode(key, value));
	else
	{
		tmp = node->value;
		node->value = ft_strjoin(node->value, value);
		free(tmp);
	}
}

int	ft_export(char *arg[], t_envnode *env)
{
	char	*key;
	char	*value;

	if (arg[1] == NULL)
		print_envnode(env);
	key = arg[1];
	value = ft_strchr(arg[1], '=') + 1;
	if (!value)
		return (1);
	if (*(ft_strchr(arg[1], '=') - 1) == '+')
	{
		*ft_strchr(arg[1], '+') = 0;
		add_value(env, key, value);
	}
	else
	{
		*ft_strchr(arg[1], '=') = 0;
		add_envnode(env, make_envnode(key, value));
	}
	return (0);
}
