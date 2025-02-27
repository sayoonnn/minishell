/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:45:24 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:47:11 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_cd(char *arg[])
{
	int		status;

	if (arg[1] == NULL || *arg[1] == 0)
		return (success);
	status = success;
	if (chdir(arg[1]) < 0)
	{
		ft_printf(2, "minishell: cd: ");
		perror(arg[1]);
		status = fail;
	}
	return (status);
}
