/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:39:40 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/20 15:39:41 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_output(char *filename, int io_fd[2], int opt)
{
	if (opt == GREAT)
	{
		if (io_fd[1] == STDOUT_FILENO)
			io_fd[1] = open_out_file(filename, O_CREAT | O_WRONLY | O_TRUNC);
		else
			io_fd[1] = dup2(open_out_file(filename, O_CREAT | O_WRONLY | O_TRUNC), io_fd[1]);
		if (io_fd[1] == -1)
			return (0);
	}
	else
	{
		if (io_fd[1] == STDOUT_FILENO)
			io_fd[1] = open_out_file(filename, O_CREAT | O_WRONLY | O_APPEND);
		else
			io_fd[1] = dup2(open_out_file(filename, O_CREAT | O_WRONLY | O_APPEND), io_fd[1]);
		if (io_fd[1] == -1)
			return (0);
	}
	return (1);
}

static int	make_input(char *filename, int io_fd[2], int opt)
{
	if (opt == LESS)
	{
		if (io_fd[0] == STDIN_FILENO)
			io_fd[0] = open_in_file(filename);
		else
			io_fd[0] = dup2(open_in_file(filename), io_fd[0]);
		if (io_fd[0] == -1)
			return (0);
	}
	else
	{
		if (io_fd[0] == STDIN_FILENO)
			io_fd[0] = get_heredoc_fd(filename);
		else
			io_fd[0] = dup2(get_heredoc_fd(filename), io_fd[0]);
		if (io_fd[0] == -1)
			return (0);
	}
	return (1);
}

void	handle_redir(t_tree_node *pt, int io_fd[2])
{
	if (pt == NULL)
		return ;
	if (pt->token_type == REDIRECTION_LIST)
	{
		handle_redir(pt->left, io_fd);
		handle_redir(pt->right, io_fd);
	}
	else if (pt->token_type == REDIRECTION_INFO)
	{
		if (pt->left->token_type == GREAT || pt->left->token_type == DGREAT)
		{
			if (!make_output(pt->right->contents[0], io_fd, pt->left->token_type))
				errno = 1;
		}
		else
		{
			if (!make_input(pt->right->contents[0], io_fd, pt->left->token_type))
				errno = 1;
		}
	}
}
