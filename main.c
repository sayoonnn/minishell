/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:34:56 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/26 18:48:01 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errcode = 0;

void	free_minishell_data(t_envnode *env, t_parsing *parsing)
{
	clear_node(env);
	free_parsing(parsing);
	free(parsing);
}

int main(void)
{
	char		*line;
	t_envtree	*env;
	t_parsing	*parsing;
	extern char	**environ;

	// startup_minishell();
	set_signal();
	env = init_envp(environ);
	parsing = init_parsing_tool();
	while (true)
	{
		line = readline("$> ");
		if (!line)
			break ;
		if (!parse_line(line, parsing))
			continue ;
		excute_hub(parsing, env);
		clean_parsing_tools(parsing);
		add_history(line);
		free(line);
	}
	set_child_signal();
	free_minishell_data(env->root, parsing);
	free(env);
	exit(g_errcode);
}
