/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:18:27 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/01 22:08:28 by devpark          ###   ########.fr       */
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
# include "substitution.h"
# include "types.h"

// start
void		startup_minishell(void);
t_envtree	*init_envp(char *envp[]);
char		**tree_2_envp(t_envtree *env);
void		free_arr(char **arr);
void		cut_tree(t_tree_node *root);

// exec
void		excute_hub(t_tree_node *root, t_envtree *env);
void		exec_single_cmd(t_tree_node *node, t_envtree *env);
void		exec_pipe_cmd(t_tree_node *node, t_envtree *env, \
							int saved_fd[2], pid_t *pid);
int			exec_bin(char **argv, t_envtree *env);
char		*make_binpath(char *cmd, t_envnode *path_node);
void		find_fd(t_tree_node *node, int fd[2]);
void		reset_io(int save[2]);

int			is_builtin(char *cmd);
void		exec_builtin(char *cmd, char *argv[], t_envtree *env);
int			exec_builtin_pipe(char *cmd, char *argv[], t_envtree *env);

// signal
void		set_signal(void);
void		set_child_signal(void);
void		signal_handler(int signal);

// redirection
int			open_in_file(char *file_name);
int			open_out_file(char *file_name, int opt);
int			get_heredoc_fd(char *delimiter);
int			handle_other_redir(t_tree_node *pt, t_envtree *env);
int			handle_other_redirs(t_tree_node *pt, t_envtree *env);
int			handle_heredoc_redir(t_tree_node *pt, t_envtree *env);
int			handle_heredoc_first(t_tree_node *pt, t_envtree *env);
// void		handle_heredoc(char *file_name);

#endif
