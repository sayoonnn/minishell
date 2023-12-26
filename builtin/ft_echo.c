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

static int	find_start_idx(char *argv[], int *nflag)
{
	if (argv[1] == NULL)
		return (1);
	if (!ft_strcmp("-n", argv[1]))
	{
		*nflag = true;
		return (2);
	}
	return (1);
}

int	ft_echo(char *argv[])
{
	int	nflag;
	int	start;

	nflag = false;
	start = find_start_idx(argv, &nflag);
	while (argv[start])
	{
		printf("%s", argv[start]);
		if (argv[start + 1] != NULL)
			printf(" ");
		start++;
	}
	if (!nflag)
		printf("\n");
	return (success);
}
