/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:34:56 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/03 19:34:57 by sayoon           ###   ########.fr       */
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

int main(int ac, char *av[], char *envp[])
{
	char		*line;
	char		**tmp;
	t_envtree	*env;

	(void)ac;
	(void)av;
	startup_minishell();
	set_signal();
	env = init_envp(envp);
	line = readline("$> ");
	while (line)
	{
		tmp = ft_split(line, ' ');
		exec_single_cmd(tmp[0], tmp, env);
		int i = -1;
		while (tmp[++i])
			free(tmp[i]);
		free(tmp);
		add_history(line);
		line = readline("$> ");
	}
	clear_node(env->root);
	free(env);
}
