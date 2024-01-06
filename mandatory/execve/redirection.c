/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:39:40 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/01 22:05:17 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cknopen(char *file_name, int io_fd[2], int type, t_envtree *env)
{
	if (type == GREAT || type == DGREAT)
	{
		if (!make_output(file_name, io_fd, type))
			return (false);
	}
	else
	{
		if (!make_input(file_name, io_fd, type, env))
			return (false);
	}
	return (true);
}

int	open_in_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(2, "minishell: ");
		perror(file_name);
	}
	return (fd);
}

int	open_out_file(char *file_name, int opt)
{
	int	fd;

	fd = open(file_name, opt, 0644);
	if (fd < 0)
	{
		ft_printf(2, "minishell: ");
		perror(file_name);
	}
	return (fd);
}

int	make_output(char *filename, int io_fd[2], int opt)
{
	int	write_flag;

	write_flag = 0;
	if (io_fd[1] != STDOUT_FILENO)
		close(io_fd[1]);
	if (opt == GREAT)
		write_flag = (O_CREAT | O_WRONLY | O_TRUNC);
	else if (opt == DGREAT)
		write_flag = (O_CREAT | O_WRONLY | O_APPEND);
	io_fd[1] = open_out_file(filename, write_flag);
	if (io_fd[1] == -1)
		return (false);
	return (true);
}

int	make_input(char *filename, int io_fd[2], int opt, t_envtree *env)
{
	if (io_fd[0] != STDIN_FILENO)
		close(io_fd[0]);
	if (opt == LESS)
		io_fd[0] = open_in_file(filename);
	else if (opt == DLESS)
		io_fd[0] = get_heredoc_fd(filename, env);
	if (io_fd[0] == -1)
		return (false);
	return (true);
}
