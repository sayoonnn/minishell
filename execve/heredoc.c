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

int	get_heredoc_fd(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) < 0)
		exit(1);
	line = readline("> ");
	while (line)
	{
		if(!ft_strcmp(line, delimiter))
			break ;
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		free(line);
		line = readline("> ");
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	trave_redir(t_tree_node *pt)
{
	if (pt == NULL)
		return ;
	if (pt->token_type == CMD)
	{
		pt->fd[0] = 0;
		pt->fd[1] = 1;
		handle_redir(pt->right, pt->fd);
	}
	trave_redir(pt->left);
	trave_redir(pt->right);
}
