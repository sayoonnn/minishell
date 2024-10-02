/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:34:57 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:48:17 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	print_envnode(t_envnode *tree)
{
	if (tree == NULL)
		return ;
	print_envnode(tree->left);
	if (tree->value != NULL)
		printf("%s=%s\n", tree->key, tree->value);
	print_envnode(tree->right);
}

int	ft_env(t_envnode *envp)
{
	print_envnode(envp);
	return (success);
}
