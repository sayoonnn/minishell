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

int	ft_export(t_envnode *env, char *str)
{
	char	**tmp;

	// export 에 인자가 없는 경우 구현해야함
	tmp = ft_split(str, '=');
	add_envnode(env, make_envnode(tmp[0], tmp[1]));
	return (0);
}
