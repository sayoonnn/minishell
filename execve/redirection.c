/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:03:50 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/05 18:03:51 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_left_bracket(char *fname)
{
	int	fd;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
	{
		perror(fname);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		//에러처리
		return ;
}

void	handle_right_bracket(char *fname)
{
	int	fd;

	fd = open(fname, O_CREAT);
	if (fd < 0)
	{
		perror(fname);
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		//에러처리
		return ;
}

void	handle_dright_bracket(char *fname)
{
	int	fd;

	fd = open(fname, O_CREAT | O_APPEND);
	if (fd < 0)
	{
		perror(fname);
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
		//에러처리
		return ;
}
