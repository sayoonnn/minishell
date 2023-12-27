/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:27:06 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 20:27:08 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_FUNC_H
# define BUILT_IN_FUNC_H

int		ft_cd(char *arg[], t_envtree *env);
int		ft_echo(char *arg[]);
int		ft_env(t_envnode *envp);
int		ft_exit(char **argv, int is_pipe);
int		ft_export(char *arg[], t_envtree *env);
int		ft_pwd(void);
int		ft_unset(t_envtree *env, char *arg[]);

#endif
