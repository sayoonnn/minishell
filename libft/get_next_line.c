/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:08:14 by sayoon            #+#    #+#             */
/*   Updated: 2023/10/10 21:31:23 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*string;
	char		*nl_idx;

	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		*buffer = 0;
		return (NULL);
	}
	string = NULL;
	nl_idx = gnl_memchr(buffer, '\n', gnl_strlen(buffer));
	if (nl_idx)
	{
		string = gnl_strdup(buffer, nl_idx - buffer + 1);
		gnl_memcpy(buffer, nl_idx + 1, gnl_strlen(nl_idx + 1));
		return (string);
	}
	if (*buffer != 0)
	{
		string = gnl_strdup(buffer, gnl_strlen(buffer));
		if (!string)
			return (NULL);
	}
	return (ft_makestr(fd, string, buffer));
}

char	*ft_makestr(int fd, char *string, char *buffer)
{
	int		rbytes;
	char	*nl_idx;
	char	*tmp;

	rbytes = read(fd, buffer, BUFFER_SIZE);
	buffer[rbytes] = 0;
	while (rbytes > 0)
	{
		tmp = string;
		nl_idx = gnl_memchr(buffer, '\n', rbytes);
		if (nl_idx)
		{
			string = gnl_strjoin(string, buffer, nl_idx - buffer + 1);
			free(tmp);
			gnl_memcpy(buffer, nl_idx + 1, gnl_strlen(nl_idx + 1));
			break ;
		}
		string = gnl_strjoin(string, buffer, rbytes);
		free(tmp);
		rbytes = read(fd, buffer, BUFFER_SIZE);
		buffer[rbytes] = 0;
	}
	return (string);
}
