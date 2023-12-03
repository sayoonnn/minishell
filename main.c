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
		printf("\033[0;36m%s\033[0;38m", buffer);
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
} 

int main(int ac, char *av[], char *envp[])
{
	char		*line;
	t_envnode	*env;

	(void)ac;
	(void)av;
	startup_minishell();
	set_signal();
	env = init_envp(envp);
	line = readline("$> ");
	while (line)
	{
		if (!ft_strcmp(line, "env"))
			ft_env(env);
		if (!ft_strncmp(line, "cd", 2))
		{
			char *tmp[2];
			tmp[0] = line;
			tmp[1] = ft_strchr(line, ' ') + 1;
			ft_cd(tmp, env);
			printf("%s\n", getcwd(NULL, 4096));
		}
		if (!ft_strncmp(line, "export", 6))
		{
			char *tmp[2];
			tmp[0] = line;
			tmp[1] = ft_strchr(line, ' ') + 1;
			ft_export(tmp, env);
		}
		free(line);
		line = readline("$> ");
	}
	clear_node(env);
}
