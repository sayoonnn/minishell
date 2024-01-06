/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:34:56 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 15:11:21 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	g_errcode = 0;

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_envtree	*env;
	t_parsing	*parsing;

	(void)ac;
	(void)av;
	startup_minishell();
	set_signal();
	env = init_envp(envp);
	parsing = init_parsing_tool();
	while (true)
	{
		line = get_input();
		if (!line)
			break ;
		if (*line != 0)
			add_history(line);
		if (!parse_line(line, parsing))
			continue ;
		excute_hub(parsing->root, env);
		clean_parsing_tools(parsing);
		free(line);
	}
	goodbye_minishell(env, parsing);
}
