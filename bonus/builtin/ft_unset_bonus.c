/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:34:16 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:48:15 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_unset(t_envtree *env, char *arg[])
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (!check_is_valid(arg[i]))
		{
			ft_printf(2, "minishell: unset: `%s': not a valid identifier\n", \
			arg[i]);
			return (fail);
		}
		if (find_envnode(env->root, arg[i]))
		{
			env->num_nodes--;
			env->root = delete_envnode(env->root, arg[i]);
		}
		i++;
	}
	return (success);
}
