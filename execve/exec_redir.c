/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:20:34 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/20 14:20:41 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_in_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		perror(file_name);
	return (fd);
}

int	open_out_file(char *file_name, int opt)
{
	int	fd;

	fd = open(file_name, opt, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		perror(file_name);
	return (fd);
}
