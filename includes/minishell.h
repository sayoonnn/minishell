/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:18:27 by sayoon            #+#    #+#             */
/*   Updated: 2023/11/29 17:18:28 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "libft.h"
# include "env_tree.h"
# include "built_in_func.h"
# include "parse_tree.h"

void		set_signal(void);
t_envtree	*init_envp(char *envp[]);
void		print_enoent(char *pname, char *dirname);
char		**make_envp(t_envtree *env);
char		*make_command(char *cmd, t_envnode *path_node);
void		exec_single_cmd(char *cmd, char *argv[], t_envtree *env);
void		free_arr(char **arr);
char		*make_tmpfile(char *end);
void		handle_heredoc(char *file_name);
int			parse_line(char *line);
void		cut_tree(t_tree_node *root);


#endif
