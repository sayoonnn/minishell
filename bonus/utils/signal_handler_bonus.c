/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:49:30 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 13:22:41 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	set_signal(void)
{
	struct termios	term;
	int				termfd;

	termfd = ttyslot();
	tcgetattr(termfd, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(termfd, TCSANOW, &term);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signal(void)
{
	struct termios	term;
	int				termfd;

	termfd = ttyslot();
	tcgetattr(termfd, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(termfd, TCSANOW, &term);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_errcode = 1;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}
