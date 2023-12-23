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

static char	*heredoc(char *delimiter);
static char	*append_line(char *dst, char *src);

int		get_heredoc_fd(char *delimiter)
{
	int		pipe_fd[2];
	char	*doc;

	doc = heredoc(delimiter);
	if (!doc)
	{
		// err_code = 1;
		return (-1);
	}
	if (pipe(pipe_fd) < 0)
		exit(1);
	write(pipe_fd[1], doc, ft_strlen(doc));
	close(pipe_fd[1]);
	free(doc);
	return (pipe_fd[0]);

}

static char	*append_line(char *dst, char *src)
{
	char *tmp;
	
	if (!dst)
		dst = ft_strdup("");
	tmp = dst;
	dst = ft_strjoin(dst, src);
	free(tmp);
	tmp = dst;
	dst = ft_strjoin(dst, "\n");
	free(tmp);
	tmp = dst;
	return (tmp);
}

static char	*heredoc(char *delimiter)
{
	char	*line;
	char	*doc;

	doc = NULL;
	line = readline("> ");
	while (line)
	{
		if (!ft_strcmp(delimiter, line))
			break ;
		doc = append_line(doc, line);
		line = readline("> ");
	}
	free(line);
	return (doc);
}
