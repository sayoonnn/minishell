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
	if (*str == 0)
		return (false);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (*str == 0)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ' ')
			return (false);
		str++;
	}
	return (true);
}

static int	ft_myatoi(const char *str, int *is_flowed)
{
	int				sign;
	int				i;
	unsigned long	ret;
	unsigned long	temp;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign *= -1;
	i += (str[i] == '+' || str[i] == '-');
	ret = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = ret * 10 + (str[i] - '0');
		if (temp > LONG_MAX || ret > temp)
		{
			*is_flowed = true - (temp == -(unsigned long)LONG_MIN && sign < 0);
			return (-1 + (sign < 0));
		}
		ret = temp;
		i++;
	}
	return (ret * sign);
}

static int	get_status(int argc, char **argv, int *can_exit)
{
	int	status;
	int	is_flowed;

	is_flowed = false;
	status = g_errcode;
	if (argc >= 2)
	{
		status = ft_myatoi(argv[1], &is_flowed);
		if (!ft_isnumber(argv[1]) || is_flowed)
		{
			ft_printf(2, "minishell: exit: %s: numeric argument required\n", \
			argv[1]);
			status = 255;
		}
		else if (argc > 2)
		{
			ft_printf(2, "minishell: exit: too many arguments\n");
			*can_exit = false;
			status = 1;
		}
	}
	return (status);
}

int	ft_exit(char **argv, int is_pipe)
{
	int		status;
	int		can_exit;
	int		i;

	i = 0;
	can_exit = true;
	while (argv[i])
		i++;
	if (!is_pipe)
		ft_printf(2, "exit\n");
	status = get_status(i, argv, &can_exit);
	if (can_exit)
		exit(status);
	else
		return (status);
}
