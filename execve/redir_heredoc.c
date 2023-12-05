/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:05:38 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/05 20:05:39 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char make_randchar(int c)
{
	char	*tmp = "0123456789abcdefghijklmnopqr\
	stuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (c < 0)
		c *= -1;
	c %= 62;
	printf("%c\n", tmp[c]);
	return (tmp[c]);
}

static char	*name_file(void)
{
	int		fd;
	char	buffer[10];
	char	*tmp;
	int		j;
	int		i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		exit(1);
	if (read(fd, buffer, 10) < 0)
		exit(1);
	tmp = malloc(sizeof(char) * 18);
	if (!tmp)
		exit(1);
	tmp[0] = 0;
	tmp[17] = 0;
	ft_strlcat(tmp, "heredoc", 18);
	i = 7;
	j = 0;
	while (j < 10)
		tmp[i++] = make_randchar(buffer[j++]);
	return (tmp);
}

char	*make_tmpfile(char *end)
{
	char	*file_name;
	char	*tmp;
	int		fd;
	char	*line;

	tmp = name_file();
	printf("%s\n", tmp);
	file_name = ft_strjoin("/tmp/", tmp);
	printf("%s\n", file_name);
	free(tmp);
	fd = open(file_name, O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
		exit(1);
	line = readline("> ");
	while (line && ft_strcmp(line, end))
	{
		if (write(fd, line, ft_strlen(line)) < 0)
			exit(1);
		if (write(fd, "\n", 1) < 0)
			exit(1);
		free(line);
		line = readline("> ");
	}
	close(fd);
	return (file_name);
}

void	handle_heredoc(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror(file_name);
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		//에러처리
		return ;
}
