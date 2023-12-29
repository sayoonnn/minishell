/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:22:55 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 19:22:56 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumber(char *str)
{
	int	num_cnt;

	num_cnt = 0;
	if (*str == 0)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static int	get_status(int argc, char **argv)
{
	int			status;

	status = g_errcode;
	if (argc >= 2)
	{
		if (!ft_isnumber(argv[1]))
		{
			ft_printf(2, "minishell: exit: %s: numeric argumet required\n", argv[1]);
			status = 2;
		}
		else if (argc > 2)
		{
			ft_printf(2, "minishell: exit: too many arguments\n");
			status = 255;
		}
		else
			status = ft_atoi(argv[1]);
	}
	return (status);
}

int	ft_exit(char **argv, int is_pipe)
{
	int		status;
	int		is_errd;
	int		i;

	(void)is_pipe;
	i = 0;
	is_errd = false;
	while (argv[i])
		i++;
	status = get_status(i, argv);
	// if (!is_pipe)
	// 	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(status);
}
