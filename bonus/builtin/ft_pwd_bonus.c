/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:59:00 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:48:12 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

#include <limits.h>
#include <unistd.h>
#include <stdio.h>

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
	{
		ft_printf(2, "minishell: pwd: ");
		perror("");
		return (1);
	}
	printf("%s\n", path);
	return (0);
}
