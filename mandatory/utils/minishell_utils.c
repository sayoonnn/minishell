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

void	startup_minishell(void)
{
	int		fd;
	char	buffer;
	int		read_bytes;

	fd = open("mandatory/utils/startup.txt", O_RDONLY);
	if (fd < 0)
		exit(1);
	read_bytes = read(fd, &buffer, 1);
	while (read_bytes > 0)
	{
		write(1, &buffer, 1);
		read_bytes = read(fd, &buffer, 1);
	}
	close(fd);
}

void	free_minishell_data(t_envtree *env, t_parsing *parsing)
{
	clear_node(env->root);
	free(env);
	free_parsing(parsing);
	free(parsing);
}

char	*get_input(void)
{
	if (g_errcode)
		return (readline("\033[0;31m✘ \033[0\033[0;34mminishell$ \033[0m"));
	else
		return (readline("\033[0;34mminishell$ \033[0m"));
}

void	goodbye_minishell(t_envtree *env, t_parsing *parsing)
{
	set_child_signal();
	free_minishell_data(env, parsing);
	printf("exit\n");
	exit(g_errcode);
}
