/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:34:57 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 19:34:57 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
