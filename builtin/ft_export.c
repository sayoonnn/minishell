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
	if (tree->value == NULL)
		printf("declare -x %s\n", tree->key);
	else
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

static void	check_n_add(char *key, char *value, t_envtree *env)
{
	if (!value)
		add_env(env, make_envnode(key, NULL));
	else if (*(value - 1) == '+')
	{
		*(value - 1) = 0;
		add_value(env, key, value + 1);
	}
	else
	{
		*value = 0;
		add_env(env, make_envnode(key, value + 1));
	}
}

static int	check_is_valid(char *key)
{
	int	i;

	i = 0;
	while (key[i] && key[i] != '=' && key[i] != '+')
	{
		if (i == 0 && (!ft_isalpha(key[i]) && key[i] != '_'))
			return (false);
		if (key[i] == '_')
		{
			i++;
			continue ;
		}
		if (!ft_isalnum(key[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_export(char *arg[], t_envtree *env)
{
	char	*key;
	char	*value;
	int		ret;
	int		i;

	ret = success;
	if (arg[1] == NULL)
	{
		print_envnode(env->root);
		return (ret);
	}
	i = 0;
	while (arg[++i])
	{
		key = arg[i];
		value = ft_strchr(arg[i], '=');
		if (!check_is_valid(key))
		{
			ft_printf(2, "minishell: export: `%s': %s\n", key, ERR_IDENIFIER);
			ret = fail;
			continue ;
		}
		check_n_add(key, value, env);
	}
	return (ret);
}
