/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:27:47 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/01 22:06:06 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

static void	exit_readline(int signal)
{
	if (signal == SIGINT)
	{
		rl_done = 1;
		g_errcode = 1;
		set_signal();
	}
}

static int	none(void)
{
	return (1);
}

static void	write_to_pipe(char *line, t_envtree *env, int pipe_fd)
{
	char	*tmp;

	tmp = ft_strdup("");
	substitute_dollar_heredoc(line, env, &tmp);
	ft_printf(pipe_fd, "%s\n", tmp);
	free(tmp);
	free(line);
}

static int	close_and_return(int pipe[2], char *line)
{
	close(pipe[0]);
	close(pipe[1]);
	free(line);
	return (-1);
}

int	get_heredoc_fd(char *delimiter, t_envtree *env)
{
	int		pipe_fd[2];
	char	*line;

	signal(SIGINT, exit_readline);
	rl_event_hook = none;
	if (pipe(pipe_fd) < 0)
		exit(1);
	g_errcode = 0;
	while (true)
	{
		line = readline("> ");
		if (rl_done == 1 && g_errcode == 1)
			return (close_and_return(pipe_fd, line));
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(line) + 1))
		{
			free(line);
			break ;
		}
		write_to_pipe(line, env, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
