/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:25:38 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/03 15:26:47 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_exports(t_envnode *tree)
{
	if (tree == NULL)
		return (success);
	print_exports(tree->left);
	if (tree->value == NULL)
		printf("declare -x %s\n", tree->key);
	else
		printf("declare -x %s=\"%s\"\n", tree->key, tree->value);
	print_exports(tree->right);
	return (success);
}

void	add_value(t_envtree *env, char *key, char *value)
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

void	check_n_add(char *key, char *value, t_envtree *env)
{
	if (!value)
		add_env(env, make_envnode(key, NULL));
	else if (*value == '+')
		add_value(env, key, value + 2);
	else
		add_env(env, make_envnode(key, value + 1));
}

int	check_is_valid(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (false);
	while (key[i])
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
