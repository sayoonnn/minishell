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

static int	find_start_idx(char *argv[], int *nflag)
{
	size_t	i;
	int		cnt;
	int		start_idx;

	start_idx = 1;
	if (argv[1] == NULL)
		return (1);
	while (argv[start_idx] != NULL && *argv[start_idx] == '-')
	{
		cnt = 0;
		i = 1;
		while (argv[1][i])
		{
			if (argv[1][i] == 'n')
				cnt++;
			i++;
		}
		if ((size_t)cnt == i - 1)
			*nflag = true;
		else
			return (start_idx);
		start_idx++;
	}
	return (start_idx);
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
