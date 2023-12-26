/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startup_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:50:34 by devpark           #+#    #+#             */
/*   Updated: 2023/12/26 14:50:43 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	startup_minishell(void)
{
	int		fd;
	char	*buffer;

	fd = open("./utils/startup.txt", O_RDONLY);
	if (fd < 0)
		exit(1);
	buffer = get_next_line(fd);
	while (buffer)
	{
		printf("\033[0;32m%s\033[0;38m", buffer);
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
}