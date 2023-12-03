/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:47:40 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 20:47:40 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_in_func.h"

int	ft_unset(t_envnode *env, char *arg[])
{
	if (arg[1] == NULL)
		return ;
	delete_envnode(env, arg[1]);
	return (1);
}
