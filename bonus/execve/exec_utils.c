/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:56:33 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/05 14:56:33 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_binpath(char *cmd, t_envnode *path_node)
{
	int			i;
	char		**path;
	char		*tmp;
	char		*command;

	if (!path_node || path_node->value == NULL || *cmd == 0)
		return (NULL);
	path = ft_oldsplit(path_node->value, ':');
	tmp = ft_strjoin("/", cmd);
	i = -1;
	while (path[++i])
	{
		command = ft_strjoin(path[i], tmp);
		if (!access(command, F_OK))
		{
			free(tmp);
			free_perfectly_split(path);
			return (command);
		}
		free(command);
	}
	free(tmp);
	free_perfectly_split(path);
	return (NULL);
}

void	find_fd(t_tree_node *node, int fd[2])
{
	if (node == NULL)
		return ;
	if (node->token_type == REDIRECTION_INFO)
	{
		if (node->fd[0] != 0)
		{
			if (fd[0] != 0)
				close(fd[0]);
			fd[0] = node->fd[0];
		}
		if (node->fd[1] != 1)
		{
			if (fd[1] != 1)
				close(fd[1]);
			fd[1] = node->fd[1];
		}
	}
	find_fd(node->left, fd);
	find_fd(node->right, fd);
}

void	undo_setting(int saved_fd[2], pid_t last_pid, t_tree_node *node)
{
	signal(SIGINT, SIG_IGN);
	waitpid(last_pid, &g_errcode, 0);
	while (wait(NULL) != -1)
		;
	if (WIFSIGNALED(g_errcode))
	{
		if (WTERMSIG(g_errcode) == SIGQUIT)
			printf("Quit: 3");
		printf("\n");
		g_errcode = (128 + WTERMSIG(g_errcode));
	}
	else
		g_errcode = WEXITSTATUS(g_errcode);
	reset_io(saved_fd);
	saved_fd[0] = -1;
	saved_fd[1] = -1;
	set_signal();
	close_heredoc(node);
}

void	close_heredoc(t_tree_node *node)
{
	if (node == NULL)
		return ;
	if (node->token_type == PIPE)
	{
		close_heredoc(node->left);
		close_heredoc(node->right);
	}
	else if (node->token_type == CMD)
	{
		if (node->fd[0] != 0)
			close(node->fd[0]);
		if (node->fd[1] != 1)
			close(node->fd[1]);
	}
	return ;
}
