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
# include "errors.h"

void		set_signal(void);
t_envtree	*init_envp(char *envp[]);
void		print_err(char *pname, char *dirname);
char		**tree_2_envp(t_envtree *env);
char		*make_binpath(char *cmd, t_envnode *path_node);
void		exec_single_cmd(char *argv[], t_envtree *env, int fd[2]);
int			exec_bin(char **argv, t_envtree *env);
void		excute_hub(t_tree_node *pt, t_envtree *env);

int			is_builtin(char *cmd);
void		exec_builtin(char *cmd, char *argv[], t_envtree *env);
void		reset_io(int save[2]);
void		free_arr(char **arr);

// redirection
int		open_in_file(char *file_name);
int		open_out_file(char *file_name, int opt);
int		get_heredoc_fd(char *delimiter);
void	handle_redir(t_tree_node *pt, int io_fd[2]);



char			*make_tmpfile(char *end);
void			handle_heredoc(char *file_name);
t_tree_node     *parse_line(char *line);
void			exec_multi_cmd(char *cmd, char *argv[], t_envtree *env);
void			cut_tree(t_tree_node *root);

#endif
