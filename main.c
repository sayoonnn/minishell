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

int	err_code = 0;

void	free_minishell_data(t_envnode *env, t_parsing *parsing)
{
	clear_node(env);
	free_parsing(parsing);
	free(parsing);
	free(env);
}

int main(void)
{
	char		*line;
	t_tree_node	*parse_tree;
	t_envtree	*env;
	t_parsing	*parsing;
	extern char	**environ;

	startup_minishell();
	set_signal();
	env = init_envp(environ);
	parsing = init_parsing_tool();
	line = readline("$> ");
	while (line)
	{
		if (line != NULL)
		{
			parse_line(line, parsing);
			excute_hub(parsing, env);
			clean_parsing_tools(parsing);
			parse_tree = NULL;
			if (ft_strncmp(line, "", 1))
				add_history(line);
			free(line);
		}
		line = readline("$> ");
	}
	free_minishell_data(env, parsing);
	return (EXIT_SUCCESS);
}
