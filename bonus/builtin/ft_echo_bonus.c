/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:08:09 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:48:06 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
		ft_printf(1, "%s", argv[start]);
		if (argv[start + 1] != NULL)
			ft_printf(1, " ");
		start++;
	}
	if (!nflag)
		ft_printf(1, "\n");
	return (success);
}
