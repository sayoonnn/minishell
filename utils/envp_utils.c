/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 22:47:06 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/03 22:47:07 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envnode	*init_envp(char *envp[])
{
	t_envnode	*env;
	char		*key;
	char		*value;

	env = NULL;
	while (*envp)
	{
		key = *envp;
		value = ft_strchr(*envp, '=') + 1;
		*ft_strchr(*envp, '=') = 0;
		env = add_envnode(env, make_envnode(key, value));
		envp++;
	}
	return (env);
}
