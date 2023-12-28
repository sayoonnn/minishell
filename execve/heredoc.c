/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:27:47 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/20 16:27:48 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	event(void)
{
	return (true);
}

static void	return_2_input(int signal)
{
	if (signal == SIGINT)
	{
		g_errcode = 1;
		rl_done = true;
	}
}

int	get_heredoc_fd(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	rl_event_hook = event;
	signal(SIGINT, return_2_input);
	if (pipe(pipe_fd) < 0)
		exit(1);
	line = readline("> ");
	while (line)
	{
		if (rl_done && g_errcode == 1)
		{
			set_signal();
			close(pipe_fd[1]);
			return (-1);
		}
		if (!ft_strcmp(line, delimiter))
			break ;
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		free(line);
		line = readline("> ");
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	trave_redir(t_parsing *ps, t_envtree *env, t_tree_node *pt)
{
	if (pt == NULL)
		return (true);
	if (pt->token_type == CMD)
	{
		pt->fd[0] = 0;
		pt->fd[1] = 1;
		return (handle_redir(ps, env, pt->right, pt->fd));
	}
	if (!trave_redir(ps, env, pt->left))
		return (false);
	if (!trave_redir(ps, env, pt->right))
		return (false);
	return (true);
}
