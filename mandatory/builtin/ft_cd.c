/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:45:24 by sayoon            #+#    #+#             */
/*   Updated: 2023/11/30 20:45:25 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
