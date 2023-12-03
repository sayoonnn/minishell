/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:08:09 by sayoon            #+#    #+#             */
/*   Updated: 2023/11/30 20:08:13 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static size_t	ft_arrlen(char *arr[])
{
	size_t	i;

	i = 0;
	while (*arr++)
		i++;
	return (i);
}

int	ft_echo(char *arg[])
{
	size_t	i;

	i = ft_arrlen(arg);
	if (i == 1)
		printf("\n");
	else if (i == 2)
	{
		if (!ft_strcmp(arg[1], "-n"))
			printf("");
		else
			printf("%s\n", arg[1]);
	}
	else
	{
		if (!ft_strcmp(arg[1], "-n"))
			printf("%s", arg[2]);
		else
			printf("%s\n", arg[2]);
	}
	return (0);
}
