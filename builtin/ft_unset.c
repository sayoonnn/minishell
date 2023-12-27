/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:34:16 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/05 16:34:17 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_envtree *env, char *arg[])
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (find_envnode(env->root, arg[i]))
		{
			env->num_nodes--;
			env->root = delete_envnode(env->root, arg[i]);
		}
		i++;
	}
	return (success);
}
