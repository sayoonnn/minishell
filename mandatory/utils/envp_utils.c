/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 22:47:06 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/09 14:19:55 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envtree	*init_envp(char *envp[])
{
	t_envtree	*env;
	char		*key;
	char		*value;

	env = malloc(sizeof(t_envtree));
	if (!env)
		exit(-1);
	env->root = NULL;
	env->num_nodes = 0;
	while (*envp)
	{
		key = *envp;
		value = ft_strchr(*envp, '=') + 1;
		*ft_strchr(*envp, '=') = 0;
		env->root = add_envnode(env->root, make_envnode(key, value));
		env->num_nodes++;
		envp++;
	}
	return (env);
}

static void	make_arr(t_envtree *tree, t_envnode *env, char **envp)
{
	static int	i = 0;

	if (tree->num_nodes == 0)
		return ;
	if (tree->root == env)
		i = 0;
	if (env == NULL)
		return ;
	make_arr(tree, env->left, envp);
	if (env->value != NULL)
		envp[i++] = env->forarr;
	make_arr(tree, env->right, envp);
}

char	**tree_2_envp(t_envtree *env)
{
	char	**tmp;

	tmp = ft_calloc(sizeof(char *), (env->num_nodes + 1));
	if (!tmp)
		exit(1);
	make_arr(env, env->root, tmp);
	tmp[env->num_nodes] = NULL;
	return (tmp);
}
