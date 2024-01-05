/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:27:47 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 16:05:05 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
	free(line);
	return (pipe_fd[0]);
}

int	handle_heredoc_first(t_tree_node *pt, t_envtree *env)
{
	if (pt == NULL)
		return (true);
	if (pt->token_type == CMD)
		return (handle_heredoc_redir(pt->right, env));
	if (!handle_heredoc_first(pt->left, env))
		return (false);
	if (!handle_heredoc_first(pt->right, env))
		return (false);
	return (true);
}

int	handle_other_redirs(t_tree_node *pt, t_envtree *env)
{
	if (pt == NULL)
		return (true);
	if (pt->token_type == CMD)
		return (handle_other_redir(pt->right, env));
	if (!handle_other_redirs(pt->left, env))
		return (false);
	if (!handle_other_redirs(pt->right, env))
		return (false);
	return (true);
}
